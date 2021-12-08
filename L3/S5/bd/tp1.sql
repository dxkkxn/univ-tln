CREATE TABLE Departement(
    DID varchar(2) PRIMARY KEY,
    Libelle varchar(20)
  );

CREATE TABLE Employe (
    EID integer primary key CHECK (eid > 9 and eid < 100),
    Nom varchar(20),
    Dept varchar(2), 
    CONSTRAINT employe_departement_fkey FOREIGN KEY (Dept) REFERENCES Departement(did));
INSERT INTO departement VALUES ("mt", math);

ERROR:  syntax error at or near "clear"
LINE 1: clear
        ^
ybenjello021=> show search_path;
  search_path   
----------------
 "$user",public
(1 row)

ybenjello021=> create schema tp1
ybenjello021-> show search_path;
ERROR:  syntax error at or near "show"
LINE 2: show search_path;
        ^
ybenjello021=> create schema tp1;
CREATE SCHEMA
ybenjello021=> show search-path;
ERROR:  syntax error at or near "-"
LINE 1: show search-path;
                   ^
ybenjello021=> show search_path;
  search_path   
----------------
 "$user",public
(1 row)

ybenjello021=> show search_path;\d publi 
  search_path   
----------------
 "$user",public
(1 row)

Did not find any relation named "publi".
ybenjello021=> show search_path;\d public
  search_path   
----------------
 "$user",public
(1 row)

Did not find any relation named "public".
ybenjello021=> \d public;
Did not find any relation named "public".
ybenjello021=> set search-path to tp1, public;
ERROR:  syntax error at or near "-"
LINE 1: set search-path to tp1, public;
                  ^
ybenjello021=> set search_path to tp1, public;
SET
ybenjello021=> show search_path
ybenjello021-> ;
 search_path 
-------------
 tp1, public
(1 row)

ybenjello021=> CREATE TABLE Departement(DID varchar(2) PRIMARY KEY, Libelle varchar(20))
ybenjello021-> ;
CREATE TABLE
ybenjello021=> \d Departement
                     Table "tp1.departement"
 Column  |         Type          | Collation | Nullable | Default 
---------+-----------------------+-----------+----------+---------
 did     | character varying(2)  |           | not null | 
 libelle | character varying(20) |           |          | 
Indexes:
    "departement_pkey" PRIMARY KEY, btree (did)

ybenjello021=> CREATE TABLE Employe(--EID integer CHECK (EID>9 and EID < 100) EID primary key integer, Nom varchar(20), Dept varchar(2), CONSTRAINT employe_departement_fkey (Dept) REFERENCES Departement(did));
ybenjello021(> )
ybenjello021-> ;
CREATE TABLE
ybenjello021=> \d employe
              Table "tp1.employe"
 Column | Type | Collation | Nullable | Default 
--------+------+-----------+----------+---------

ybenjello021=> \d Employe
              Table "tp1.employe"
 Column | Type | Collation | Nullable | Default 
--------+------+-----------+----------+---------

ybenjello021=> \d ads
Did not find any relation named "ads".
ybenjello021=> DROP TABLE employe 
ybenjello021-> ;
DROP TABLE
ybenjello021=> \d Employe
Did not find any relation named "Employe".
ybenjello021=> CREATE TABLE Employe(--EID integer CHECK (EID>9 and EID < 100) EID primary key integer, Nom varchar(20), Dept varchar(2), CONSTRAINT employe_departement_fkey (Dept) REFERENCES Departement(did));
ybenjello021(> ;
ybenjello021(> );
ERROR:  syntax error at or near ";"
LINE 2: ;
        ^
ybenjello021=> CREATE TABLE Employe(--EID integer CHECK (EID>9 and EID < 100) EID primary key integer, Nom varchar(20), Dept varchar(2), CONSTRAINT employe_departement_fkey FOREIGN KEY (Dept) REFERENCES Departement(did))
ybenjello021(> ;
ybenjello021(> ;
ybenjello021(> )
ybenjello021-> ;
ERROR:  syntax error at or near ";"
LINE 2: ;
        ^
ybenjello021=> CREATE TABLE Employe(--EID integer CHECK (EID>9 and EID < 100) EID primary key integer, Nom varchar(20), Dept varchar(2), CONSTRAINT employe_departement_fkey FOREIGN KEY (Dept) REFERENCES Departement(did)));
ybenjello021(> ;
ybenjello021(> )
ybenjello021-> ;);
ERROR:  syntax error at or near ";"
LINE 2: ;
        ^
ERROR:  syntax error at or near ")"
LINE 1: );
        ^
ybenjello021=> CREATE TABLE Employe(--EID integer CHECK (EID>9 and EID < 100) EID primary key integer, Nom varchar(20), Dept varchar(2), CONSTRAINT employe_departement_fkey FOREIGN KEY (Dept) REFERENCES Departement(did));
ybenjello021(> )
ybenjello021-> ;
CREATE TABLE
ybenjello021=> \d employe 
              Table "tp1.employe"
 Column | Type | Collation | Nullable | Default 
--------+------+-----------+----------+---------

ybenjello021=> DROP TABLE employe;
DROP TABLE
ybenjello021=> CREATE TABLE Employe (
ybenjello021(>     EID primary key integer CHECK (eid > 9 and eid < 100),
ybenjello021(>     Nom varchar(20),
ybenjello021(>     Dept varchar(2), 
ybenjello021(>     CONSTRAINT employe_departement_fkey FOREIGN KEY (Dept) REFERENCES Departement(did));
ERROR:  syntax error at or near "primary"
LINE 2:     EID primary key integer CHECK (eid > 9 and eid < 100),
                ^
ybenjello021=> CREATE TABLE Employe (
    EID integer primary key CHECK (eid > 9 and eid < 100),
    Nom varchar(20),
    Dept varchar(2), 
    CONSTRAINT employe_departement_fkey FOREIGN KEY (Dept) REFERENCES Departement(did));
CREATE TABLE
ybenjello021=> \Employe 
invalid command \Employe
Try \? for help.
ybenjello021=> \d employe
                       Table "tp1.employe"
 Column |         Type          | Collation | Nullable | Default 
--------+-----------------------+-----------+----------+---------
 eid    | integer               |           | not null | 
 nom    | character varying(20) |           |          | 
 dept   | character varying(2)  |           |          | 
Indexes:
    "employe_pkey" PRIMARY KEY, btree (eid)
Check constraints:
    "employe_eid_check" CHECK (eid > 9 AND eid < 100)
Foreign-key constraints:
    "employe_departement_fkey" FOREIGN KEY (dept) REFERENCES departement(did)

ybenjello021=> \d departement
                     Table "tp1.departement"
 Column  |         Type          | Collation | Nullable | Default 
---------+-----------------------+-----------+----------+---------
 did     | character varying(2)  |           | not null | 
 libelle | character varying(20) |           |          | 
Indexes:
    "departement_pkey" PRIMARY KEY, btree (did)
Referenced by:
    TABLE "employe" CONSTRAINT "employe_departement_fkey" FOREIGN KEY (dept) REFERENCES departement(did)

ybenjello021=> INSERT INTO departement VALUES ("mt", math);
ERROR:  column "mt" does not exist
LINE 1: INSERT INTO departement VALUES ("mt", math);
                                        ^
ybenjello021=> INSERT INTO departement VALUES (mt, math);
ERROR:  column "mt" does not exist
LINE 1: INSERT INTO departement VALUES (mt, math);
                                        ^
ybenjello021=> INSERT INTO departement VALUES ('mt', 'math');
INSERT 0 1
ybenjello021=> \departement
invalid command \departement
Try \? for help.
ybenjello021=> \d departement
                     Table "tp1.departement"
 Column  |         Type          | Collation | Nullable | Default 
---------+-----------------------+-----------+----------+---------
 did     | character varying(2)  |           | not null | 
 libelle | character varying(20) |           |          | 
Indexes:
    "departement_pkey" PRIMARY KEY, btree (did)
Referenced by:
    TABLE "employe" CONSTRAINT "employe_departement_fkey" FOREIGN KEY (dept) REFERENCES departement(did)

ybenjello021=> show table departement 
ybenjello021-> ;
ERROR:  syntax error at or near "table"
LINE 1: show table departement 
             ^
ybenjello021=> \dt departement
              List of relations
 Schema |    Name     | Type  |    Owner     
--------+-------------+-------+--------------
 tp1    | departement | table | ybenjello021
(1 row)

ybenjello021=> SELECT * FROM departement
ybenjello021-> ;
 did | libelle 
-----+---------
 mt  | math
(1 row)

ybenjello021=> rollback
ybenjello021-> SELECT * FROM departement
;
ERROR:  syntax error at or near "SELECT"
LINE 2: SELECT * FROM departement
        ^
ybenjello021=> rollback;
WARNING:  there is no transaction in progress
ROLLBACK
ybenjello021=> delete from departement where did = 'mt'
ybenjello021-> ;
DELETE 1
ybenjello021=> select * from departement
ybenjello021-> ;
 did | libelle 
-----+---------
(0 rows)

ybenjello021=> begin transaction
ybenjello021-> INSERT INTO departement VALUES ('mt', 'math');
ERROR:  syntax error at or near "INSERT"
LINE 2: INSERT INTO departement VALUES ('mt', 'math');
        ^
ybenjello021=> begin transaction; INSERT INTO departement VALUES ('mt', 'math');
BEGIN
INSERT 0 1
ybenjello021=> select * from departement 
ybenjello021-> ;
 did | libelle 
-----+---------
 mt  | math
(1 row)

ybenjello021=> rollback
ybenjello021-> select * from departement
ybenjello021-> ;
ERROR:  syntax error at or near "select"
LINE 2: select * from departement
        ^
ybenjello021=> ;
ybenjello021=> ;
ybenjello021=> select * from departement;
ERROR:  current transaction is aborted, commands ignored until end of transaction block
ybenjello021=> end transaction
ybenjello021-> ;
ROLLBACK
ybenjello021=> select * from departement;
 did | libelle 
-----+---------
(0 rows)

ybenjello021=> select version();
ybenjello021=> select * from departement;
 did | libelle 
-----+---------
(0 rows)

ybenjello021=> begin transaction;
BEGIN
ybenjello021=> INSERT INTO departement VALUES ('mt', 'math');
INSERT 0 1
ybenjello021=> commit;
COMMIT
ybenjello021=> rollback;
WARNING:  there is no transaction in progress
ROLLBACK
ybenjello021=> begint transaction;
ERROR:  syntax error at or near "begint"
LINE 1: begint transaction;
        ^
ybenjello021=> begin transaction;
BEGIN
ybenjello021=> insert into department values ('51', 'algo graph');
ERROR:  relation "department" does not exist
LINE 1: insert into department values ('51', 'algo graph');
                    ^
ybenjello021=> insert into departement values ('51', 'algo graph');
ERROR:  current transaction is aborted, commands ignored until end of transaction block
ybenjello021=> rollback
ybenjello021-> ;
ROLLBACK
ybenjello021=> select * from 
departement          pg_catalog.          pg_toast_temp_1.     tp1_l3.
employe              pg_temp_1.           public.              
information_schema.  pg_toast.            tp1.                 
ybenjello021=> select * from departement 
ybenjello021-> ;
 did | libelle 
-----+---------
 mt  | math
(1 row)

