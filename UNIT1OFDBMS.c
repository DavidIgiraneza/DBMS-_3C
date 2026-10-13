# PL/SQL Programs – Practical Assignment

The following are 10 PL/SQL programs written in simple Oracle SQL/PLSQL format. Run them in Oracle SQL Developer or SQL\*Plus. For programs that accept input from the user, `ACCEPT` and substitution variables (`&`) are used.

Before executing the programs, enable output:

sql
```
SET SERVEROUTPUT ON;
```

## 1. Calculate Simple Interest

Formula: Simple Interest = (Principal × Rate × Time) / 100

sql
```
DECLARE
    p NUMBER(10,2);
    r NUMBER(5,2);
    t NUMBER(5,2);
    si NUMBER(10,2);
BEGIN
    p := &Principal;
    r := &Rate_of_Interest;
    t := &Number_of_Years;

    si := (p * r * t) / 100;

    DBMS_OUTPUT.PUT_LINE('Principal = ' || p);
    DBMS_OUTPUT.PUT_LINE('Rate = ' || r);
    DBMS_OUTPUT.PUT_LINE('Time = ' || t);
    DBMS_OUTPUT.PUT_LINE('Simple Interest = ' || si);
END;
/
```

## 2. Calculate Square and Cube of a Number

sql
```
DECLARE
    n NUMBER;
    sq NUMBER;
    cb NUMBER;
BEGIN
    n := &Enter_Number;

    sq := n * n;
    cb := n * n * n;

    DBMS_OUTPUT.PUT_LINE('Square = ' || sq);
    DBMS_OUTPUT.PUT_LINE('Cube = ' || cb);
END;
/
```

## 3. Calculate Discount on a Product

Formula: Discount = (Quantity × Price × Discount Percentage) / 100

sql
```
DECLARE
    pname VARCHAR2(50);
    qty NUMBER;
    price NUMBER(10,2);
    disc_per NUMBER(5,2);
    amount NUMBER(10,2);
    discount NUMBER(10,2);
    net_amount NUMBER(10,2);
BEGIN
    pname := '&Product_Name';
    qty := &Quantity;
    price := &Price;
    disc_per := &Discount_Percentage;

    amount := qty * price;
    discount := amount * disc_per / 100;
    net_amount := amount - discount;

    DBMS_OUTPUT.PUT_LINE('Product Name = ' || pname);
    DBMS_OUTPUT.PUT_LINE('Total Amount = Rs. ' || amount);
    DBMS_OUTPUT.PUT_LINE('Discount = Rs. ' || discount);
    DBMS_OUTPUT.PUT_LINE('Net Amount = Rs. ' || net_amount);
END;
/
```

## 4. Convert Feet into Centimeters, Inches and Meters

Conversion formulas:

- 1 foot = 30.48 centimeters
- 1 foot = 12 inches
- 1 foot = 0.3048 meters

sql
```
DECLARE
    feet NUMBER(10,2);
    cm NUMBER(10,2);
    inch NUMBER(10,2);
    meter NUMBER(10,2);
BEGIN
    feet := &Enter_Feet;

    cm := feet * 30.48;
    inch := feet * 12;
    meter := feet * 0.3048;

    DBMS_OUTPUT.PUT_LINE('Feet = ' || feet);
    DBMS_OUTPUT.PUT_LINE('Centimeters = ' || cm);
    DBMS_OUTPUT.PUT_LINE('Inches = ' || inch);
    DBMS_OUTPUT.PUT_LINE('Meters = ' || meter);
END;
/
```

## 5. Convert Celsius into Fahrenheit

Formula: Fahrenheit = (Celsius × 9/5) + 32

sql
```
DECLARE
    c NUMBER(5,2);
    f NUMBER(5,2);
BEGIN
    c := &Celsius;

    f := (c * 9 / 5) + 32;

    DBMS_OUTPUT.PUT_LINE('Temperature in Celsius = ' || c);
    DBMS_OUTPUT.PUT_LINE('Temperature in Fahrenheit = ' || f);
END;
/
```

## 6. Generate Numbers Using LOOP, FOR LOOP and WHILE LOOP

The following program displays numbers from 1 up to the number entered by the user using all three types of loops.

sql
```
DECLARE
    n NUMBER;
    i NUMBER;
BEGIN
    n := &Enter_Number;

    DBMS_OUTPUT.PUT_LINE('Using Simple LOOP');
    i := 1;
    LOOP
        EXIT WHEN i > n;
        DBMS_OUTPUT.PUT_LINE(i);
        i := i + 1;
    END LOOP;

    DBMS_OUTPUT.PUT_LINE('Using FOR LOOP');
    FOR i IN 1..n LOOP
        DBMS_OUTPUT.PUT_LINE(i);
    END LOOP;

    DBMS_OUTPUT.PUT_LINE('Using WHILE LOOP');
    i := 1;
    WHILE i <= n LOOP
        DBMS_OUTPUT.PUT_LINE(i);
        i := i + 1;
    END LOOP;
END;
/
```

## 7. Calculate Total, Percentage and Grade of a Student

### Step 1: Create the RESULT table

sql
```
CREATE TABLE RESULT (
    Rollno NUMBER(5) PRIMARY KEY,
    Name VARCHAR2(30),
    Sub1 NUMBER(5,2),
    Sub2 NUMBER(5,2),
    Sub3 NUMBER(5,2),
    Sub4 NUMBER(5,2),
    Sub5 NUMBER(5,2),
    Total NUMBER(6,2),
    Per NUMBER(5,2),
    Grade VARCHAR2(2)
);
```

### Step 2: Insert sample student records

sql
```
INSERT INTO RESULT
(Rollno, Name, Sub1, Sub2, Sub3, Sub4, Sub5)
VALUES (1, 'Rahul', 85, 78, 90, 88, 79);

INSERT INTO RESULT
(Rollno, Name, Sub1, Sub2, Sub3, Sub4, Sub5)
VALUES (2, 'Priya', 65, 72, 68, 70, 75);

COMMIT;
```

### Step 3: Calculate total, percentage and grade

Assumption: Each subject is out of 100, and the following grading scale is used:

- 90% and above: A
- 75% to below 90%: B
- 60% to below 75%: C
- 40% to below 60%: D
- Below 40%: F

sql
```
DECLARE
    v_rollno RESULT.Rollno%TYPE;
    v_total RESULT.Total%TYPE;
    v_per RESULT.Per%TYPE;
    v_grade RESULT.Grade%TYPE;
BEGIN
    v_rollno := &Enter_Rollno;

    SELECT (Sub1 + Sub2 + Sub3 + Sub4 + Sub5),
           (Sub1 + Sub2 + Sub3 + Sub4 + Sub5) / 5
    INTO v_total, v_per
    FROM RESULT
    WHERE Rollno = v_rollno;

    IF v_per >= 90 THEN
        v_grade := 'A';
    ELSIF v_per >= 75 THEN
        v_grade := 'B';
    ELSIF v_per >= 60 THEN
        v_grade := 'C';
    ELSIF v_per >= 40 THEN
        v_grade := 'D';
    ELSE
        v_grade := 'F';
    END IF;

    UPDATE RESULT
    SET Total = v_total,
        Per = v_per,
        Grade = v_grade
    WHERE Rollno = v_rollno;

    DBMS_OUTPUT.PUT_LINE('Total = ' || v_total);
    DBMS_OUTPUT.PUT_LINE('Percentage = ' || v_per || '%');
    DBMS_OUTPUT.PUT_LINE('Grade = ' || v_grade);

EXCEPTION
    WHEN NO_DATA_FOUND THEN
        DBMS_OUTPUT.PUT_LINE('Student Rollno not found.');
END;
/
```

To view the updated result:

sql
```
SELECT * FROM RESULT;
```

## 8. Display Gross Salary of an Employee

Salary rules:

- DA = 50% of Basic Salary
- HRA = 15% of Basic Salary
- Medical Allowance = Rs. 500
- PF = 10% of Basic Salary

Formula:

Gross Salary = Basic Salary + DA + HRA + Medical Allowance − PF

### Step 1: Create the EMP table

sql
```
CREATE TABLE EMP (
    EID NUMBER(5) PRIMARY KEY,
    EName VARCHAR2(30),
    Deptno NUMBER(5),
    Deptname VARCHAR2(30),
    Gender VARCHAR2(10),
    Age NUMBER(3),
    BasicSal NUMBER(10,2)
);
```

### Step 2: PL/SQL program

sql
```
DECLARE
    v_eid EMP.EID%TYPE;
    v_name EMP.EName%TYPE;
    v_basic EMP.BasicSal%TYPE;
    v_da NUMBER(10,2);
    v_hra NUMBER(10,2);
    v_medical NUMBER(10,2) := 500;
    v_pf NUMBER(10,2);
    v_gross NUMBER(10,2);
BEGIN
    v_eid := &Enter_EID;

    SELECT EName, BasicSal
    INTO v_name, v_basic
    FROM EMP
    WHERE EID = v_eid;

    v_da := v_basic * 0.50;
    v_hra := v_basic * 0.15;
    v_pf := v_basic * 0.10;

    v_gross := v_basic + v_da + v_hra
               + v_medical - v_pf;

    DBMS_OUTPUT.PUT_LINE('Employee Name = ' || v_name);
    DBMS_OUTPUT.PUT_LINE('Basic Salary = Rs. ' || v_basic);
    DBMS_OUTPUT.PUT_LINE('DA = Rs. ' || v_da);
    DBMS_OUTPUT.PUT_LINE('HRA = Rs. ' || v_hra);
    DBMS_OUTPUT.PUT_LINE('Medical = Rs. ' || v_medical);
    DBMS_OUTPUT.PUT_LINE('PF = Rs. ' || v_pf);
    DBMS_OUTPUT.PUT_LINE('Gross Salary = Rs. ' || v_gross);

EXCEPTION
    WHEN NO_DATA_FOUND THEN
        DBMS_OUTPUT.PUT_LINE('Employee EID not found.');
END;
/
```

## 9. Display Male Employees Working in the HR Department

This program displays all records of employees whose gender is Male and department name is HR.

sql
```
BEGIN
    FOR emp_rec IN (
        SELECT *
        FROM EMP
        WHERE UPPER(Gender) = 'MALE'
          AND UPPER(Deptname) = 'HR'
    )
    LOOP
        DBMS_OUTPUT.PUT_LINE('Employee ID = ' || emp_rec.EID);
        DBMS_OUTPUT.PUT_LINE('Name = ' || emp_rec.EName);
        DBMS_OUTPUT.PUT_LINE('Department No = ' || emp_rec.Deptno);
        DBMS_OUTPUT.PUT_LINE('Department = ' || emp_rec.Deptname);
        DBMS_OUTPUT.PUT_LINE('Gender = ' || emp_rec.Gender);
        DBMS_OUTPUT.PUT_LINE('Age = ' || emp_rec.Age);
        DBMS_OUTPUT.PUT_LINE('Basic Salary = ' || emp_rec.BasicSal);
        DBMS_OUTPUT.PUT_LINE('-------------------------');
    END LOOP;
END;
/
```

## 10. Delete an Employee Record for a Given EID

sql
```
DECLARE
    v_eid EMP.EID%TYPE;
BEGIN
    v_eid := &Enter_EID;

    DELETE FROM EMP
    WHERE EID = v_eid;

    IF SQL%ROWCOUNT > 0 THEN
        DBMS_OUTPUT.PUT_LINE('Employee record deleted successfully.');
    ELSE
        DBMS_OUTPUT.PUT_LINE('Employee EID not found.');
    END IF;
END;
/
```

To save the deletion permanently:

sql
```
COMMIT;
```
