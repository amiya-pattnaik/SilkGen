DROP TABLE XCUSTOMERS;
CREATE TABLE XCUSTOMERS (CUSTNO int  NOT NULL PRIMARY KEY, CUSTNAME   VARCHAR(20), CUSTCITY   VARCHAR(20));
  
INSERT INTO XCUSTOMERS  VALUES(1000, 'Guy, Buddy',		'Chicago'); 
INSERT INTO XCUSTOMERS  VALUES(1001, 'Rush, Otis',		'Chicago'); 
INSERT INTO XCUSTOMERS  VALUES(1002, 'Clapton, Eric',		'London'); 
INSERT INTO XCUSTOMERS  VALUES(1003, 'Green, Peter',		'London'); 
INSERT INTO XCUSTOMERS  VALUES(1004,  'Bloomfield, Mike',	'Chicago'); 
INSERT INTO XCUSTOMERS  VALUES(1005, 'King, Freddie',		'Dallas'); 
INSERT INTO XCUSTOMERS  VALUES(1006, 'King, B.B.',		'Memphis'); 


DROP TABLE Employee;
CREATE TABLE Employee (CUSTNO int  NOT NULL PRIMARY KEY, CUSTNAME   VARCHAR(20), CUSTCITY   VARCHAR(20));
  
INSERT INTO Employee VALUES(1000, 'Prethiba, Kumar',	'Chennai'); 
INSERT INTO Employee VALUES(1001, 'Rush, Otis',		'Chicago'); 
INSERT INTO Employee VALUES(1002, 'Clapton, Eric',	'London'); 
INSERT INTO Employee VALUES(1003, 'Green, Peter',	'London'); 
INSERT INTO Employee VALUES(1004, 'Bloomfield, Mike',	'Chicago'); 
INSERT INTO Employee VALUES(1005, 'King, Freddie',	'Dallas'); 
INSERT INTO Employee VALUES(1006, 'Pattnayak, Amiya',	'Cnennai');

DROP TABLE XEmployee;
CREATE TABLE XEmployee (CUSTDEPT VARCHAR(20), CUSTJOINDATE VARCHAR(20), CUSTNO int FOREIGN KEY REFERENCES Employee(CUSTNO) ON DELETE CASCADE);
  
INSERT INTO XEmployee VALUES('IME',	'10-01-2009', 1000); 
INSERT INTO XEmployee VALUES('ACoE',	'22-07-1999', 1001); 
INSERT INTO XEmployee VALUES('Testing',	'31-12-2004', 1002); 
INSERT INTO XEmployee VALUES('IME',	'29-11-2004', 1003); 
INSERT INTO XEmployee VALUES('JAVE CoE','02-05-2006', 1004); 



DROP TABLE Persons;
CREATE TABLE Persons (P_Id int NOT NULL PRIMARY KEY, LastName varchar(20), FirstName varchar(20), Address varchar(20), City varchar(20));

INSERT INTO Persons VALUES(100, 'Kumar', 'Prethiba','CTS', 	'Chennai');
INSERT INTO Persons VALUES(101, 'Pattnayak', 'Amiya','CTS',	'Chennai');
INSERT INTO Persons VALUES(102, 'Ray', 'Bikas','SBI', 		'Delhi');
INSERT INTO Persons VALUES(103, 'Nayak', 'Sunil','ACS', 	'Bangalore');


CREATE TABLE Orders (O_Id int NOT NULL PRIMARY KEY, OrderNo int NOT NULL, P_Id int FOREIGN KEY REFERENCES Persons(P_Id) ON DELETE CASCADE);

INSERT INTO Orders  VALUES(1, 77895, 100);
INSERT INTO Orders  VALUES(2, 44678, 101);
INSERT INTO Orders  VALUES(1, 22456, 102);
INSERT INTO Orders  VALUES(1, 24562, 103);

