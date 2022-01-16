# I54 - TP Transactions 
## Partie 1  
### A. Transaction unique  
### Comprendre commit et rollback 

#### 1. Créez la table `Departement(DID,Libelle)` où la clé primaire DID est un code à deux lettres, Libelle une chaîne de 20 caractères maximum. Créez la table `Employe(EID,Nom,Dept)` où la clé primaire EID est un nombre à deux chiffres, Nom une chaîne de 20 caractères maximum et Dept un code à deux lettres. Dept est clé étrangère référençant Departement.  

```sql
CREATE TABLE Departement(
DID varchar(2) PRIMARY KEY, 
Libelle varchar(20)
);
```
```sql
CREATE TABLE Employe (
  EID integer primary key CHECK (eid > 9 and eid < 100),
  Nom varchar(20),
  Dept varchar(2), 
  CONSTRAINT employe_departement_fkey FOREIGN KEY (Dept) REFERENCES   Departement(did));
```
ou
```sql
CREATE TABLE Employe (
  EID numeric(2) primary key,
  Nom varchar(20),
  Dept varchar(2), 
  CONSTRAINT employe_departement_fkey FOREIGN KEY (Dept) REFERENCES   Departement(did)
);
```
#### 2. Créez un département. Consultez la table Département. Effectuez un rollback. Consultez la table Département. Que se passe – il ?  
```sql 
INSERT INTO departement VALUES ("mt", math);
rollback;
```
Il faut commencer un transaction par defaut on est en mode autocommit

#### 3. Débutez une transaction (begin transaction). Créez un département. Consultez la table Département. Effectuez un rollback. Consultez la table à nouveau. Que se passe – il ? 
```sql 
begin transaction;
INSERT INTO departement VALUES ("mt", math);
rollback;
```

#### 4. Débutez une transaction. Créez un département. Consultez la table Département. Effectuez un Commit. Consultez la table à nouveau. Que se passe – il ?

```sql 
begin transaction;
INSERT INTO departement VALUES ("mt", math);
select * from departement;
rollback;
select * from departement;
```
Avant le rollback le departement a ete cree apres le rollback le departement a disparu

#### 5. Débutez une transaction. Créez un département. Consultez la table Département. Effectuez un Commit. Consultez la table à nouveau. Effectuez un rollback. Consultez la table à nouveau. Que se passe – il ?  

```sql 
begin transaction;
INSERT INTO departement VALUES ("mt", math);
select * from departement;
commit;
select * from departement;
```
La insertion a ete realise'

#### 6. Débutez une transaction. Insérez un nouveau département et quitter votre session. Ouvrez une nouvelle session. La dernière Transaction a-t-elle été validée ?  
Non la transaction n'a pas 'ete' valide'

#### 7. Insérez un nouveau département et quitter votre session. Ouvrez une nouvelle session. La dernière Transaction a-t-elle été validée ?  
Oui car on est  en mode autocommit par defaut.

#### **8. Commencez une transaction. Vider le contenu de la table Departement et effectuez un rollback. Consultez la table.** 
```sql
begin transaction;
truncate table departement CASCADE;
rollback;
select * from departement;
```


#### 9. Commencez une transaction. Vider le contenu de la table Departement et effectuez un Commit. Consultez la table. Comprendre les mises à jour et la transaction (vider les 2 tables)  
```sql
begin transaction;
truncate table departement CASCADE;
commit;
select * from departement;
```


#### 10. Créez un département <’C1’,’Info’>. Créez un employé <01,‘Quentin,‘C1’> appartenant au département C1. 11) Créez un département <’C1’,’Informatique’>. Que se passe-t-il ?  
```sql
insert into departement values ('C1', 'Info');
insert into employe values (01, 'Quentin', 'C1');
insert into departement values ('C1', 'Informatique')
```
La deniere insertion viole la contrainte de unicite de la cle primaire .

#### 12) Créez un employé <02,‘Grégoire’,‘C2’>. Que se passe-t-il ?  
```sql
insert into employe values (02, 'Gregoire', 'C2');
```
La contrainte de la cle etranger dept a ete viole' car C2 n'existe pas

#### 13) Supprimez le département C1. Que se passe-t-il ?  
```sql
delete from departement where did='C1';
```
On ne peut pas supprimer car 'C1' est reference ailleurs;

#### 14) Modifier la table Employé en supprimant la clé étrangère (ALTER TABLE ....DROP CONSTRAINT ...). Supprimez le département C1. Interrogez les deux tables. Expliquez les résultats. 
```sql 
alter table employe drop constraint employe_departement_fkey;
delete from departement where did='C1';
select * from departement;
select * from employe;
```
Maintenant vu qu'on a enleve la contrainte de cle etrangere on a un etat de notre table impossible.

#### 15) Vider les deux tables.  
``` sql
truncate table departement;
truncate table employe;
```
#### 16) Modifier la table Employé : Recréez la clé étrangère en mode ON DELETE CASCADE (ALTER TABLE ....ADD CONSTRAINT ...). Recréer le département C1 et l’employé 01.  
```sql 
ALTER TABLE employe ADD CONSTRAINT employe_departement_fkey FOREIGN KEY (dept) REFERENCES departement(did) ON DELETE CASCADE;
insert into departement values ('C1', 'Info');
insert into employe values (01, 'Quentin', 'C1');
```

#### 17) Supprimez le département C1. Interrogez les deux tables. Expliquez les résultats.  
```sql
delete from departement where did='C1';
select * from departement;
select * from employe;
```
Cela efface les deux entrees de tables.

#### 18) Recréer le département C1 et l'employé 01.
```sql
insert into departement values ('C1', 'Info');
insert into employe values (01, 'Quentin', 'C1');
```

#### 19. Supprimez à nouveau la clé étrangère. Recréez la clé étrangère sans le mode ON DELETE CASCADE mais avec le mode DEFERRABLE. 

```sql
alter table employe drop constraint employe_departement_fkey;
ALTER TABLE employe ADD CONSTRAINT employe_departement_fkey FOREIGN KEY (dept) REFERENCES departement(did) DEFERRABLE;
```
#### 20. Activer le mode DEFERRED avec la commande `SET CONSTRAINTS <nom_de_votre_contrainte> DEFERRED;` 
```sql
set constraints employe_departement_fkey deferred ;
```
WARNING:  SET CONSTRAINTS can only be used in transaction blocks
SET CONSTRAINTS

#### 21) Supprimez le département C1. Expliquez le résultat.
```sql
begin transaction;
set  constraints employe_departement_fkey deferred;
delete  from departemente where did='C1';
commit;
```
Lors du delete on a pas de message de error, c'est juste lors du commit que le message apparait.
- - - -
### B. Contrôle de la Concurrence
#### 1. Connectez-vous à votre base à partir de deux sessions différentes, simultanément.
` Pour préparer la partie B, supprimer la clé étrangère pour la recréer
sans mode DEFFERABLE ni On DELETE CASCADE. Videz la table Employé, puis
la table Departement. `
```sql
alter table employe drop constraint employe_departement_fkey;
ALTER TABLE employe ADD CONSTRAINT employe_departement_fkey FOREIGN KEY (dept) REFERENCES departement(did);
```
#### 2. Dans chacune des deux fenêtres, insérez un département (code C1 pour transaction 1, code C2 pour transaction 2). Consulter la table depuis chaque fenêtre. Que constate-t-on ? 
```sql
--terminal 1
insert into departement values ('C1', 'informatique');
```
```sql
--terminal 2
insert into department values ('C2', 'math');
```
Les deux valeurs s'inserent correctement car on est en mode auto commit par defaut.
#### 3. Dans chacune des deux fenêtres, commencez une transaction. 
 1. Insérez un département dans la session 1. Consultez la table. N’effectuez pas encore de commit. 
 2. Insérez un autre dpt dans la session2. Commitez dans la session2.
 3. Consulter la table dans les 2 sessions. Que constate-t-on ? 
 4. Commitez dans la session 1.
 5. Consulter la table dans les 2 sessions. Que constate-t-on ? 

```sql
--terminal 1
insert into departement values ('C3', 'bio');
select * from departement;
```
```sql
--terminal 2
insert into department values ('C4', 'svt');
commit;
```
```sql
--terminal 2
commit;
select * from departement;
```
```sql
--terminal 1
select * from departement;
```
```sql
--terminal 1
commit;
select * from departement;
```
```sql
--terminal 2
select * from departement;
```
Lors qu'on fait un commit la table se met `a jour meme dans des transaction ouverts en paralel
#### 4. Dans chacune des deux fenêtres, commencez une transaction.
1. Insérez un département dans la session 1. N’effectuez pas encore de commit.
2. Insérez le même département dans la session 2. Que constatez vous ?
3. Commitez dans la session 1. Que constatez-vous dans la session 2 ?
4. Terminez la session 2.
5.  Consulter la table dans les 2 sessions. Que constate-t-on ? 

```sql
--terminal 1
insert into departement values ('C5', 'algo');
--terminal 2
insert into department values ('C5', 'algo');
```
Le terminal 2  se  met en attente
```sql
--terminal 1
commit;
```
Le terminal 2 n'est plus en attente et renvoie une erreur de violation de la contrainte d'unicite de la cle primaire
```sql
--terminal 2
quit;
select * from departement;
--terminal 1
select * from departement;
```
La valeur a e'te' insere'e dans les deux sesions;
#### 5. Dans chacune des deux fenêtres, commencez une transaction. 
1. Insérez un département dans la session 1. N’effectuez pas encore de commit. 
2. Insérez le même département dans la session 2. Que constatez vous ? 
3. Annulez l’insertion dans la session 1. Que constatez-vous dans la session 2 ?
4. Terminez la session 
5. Consulter la table dans les 2 sessions. Que constate-t-on ?

```sql
--terminal 1
insert into departement values ('C6', 'poo');
--terminal 2
insert into department values ('C6', 'poo');
```
Le terminal 2  se  met en attente
```sql
--terminal 1
rollback;
```
Le terminal 2 n'est plus en attente et reussi a inserer la valeur
```sql
--terminal 2
quit;
select * from departement;
--terminal 1
select * from departement;
```
Les valeur on bien ete inseree


#### 6. Dans l’un des 2 sessions, vider le contenu de la table Departement (c’est un autocommit).
```sql
truncate table departement on cascade
```

#### 7. Dans la session 1, commencez une transaction et insérez le département <’C1’,’Info’>. Effectuer un Commit. Consultez la table Departement. 
```sql
--terminal 1
insert into departement values ('C1', 'info');
commit;
select * from departement;
```

#### 8. Depuis la session 2, commencez une transaction et modifiez le libellé de ce département en ‘Informatique’ et validez 
```sql
begin transaction;
update departement set libelle = 'Info' where did='C1';
commit;
```
#### 9. Depuis la session 1, consultez la table Departement à nouveau. 
```sql 
select * from departement
```
Le libelle a bien ete change
#### 10. Depuis la session 1 commencez une transaction. modifiez le libellé de ce département en ‘Info’ sans validez encore ; faites la même chose dans la session 2, mais pour modifier ce libelle en ‘Biologie’. Que se passe-t-il ?
```sql
--terminal 1
begin transaction;
update departement set libelle='informatique' where did='C1';
-- terminal 2
update departement set libelle='biologie' where did='C1';
```
Le terminal 2 se met en attente,
#### 11. Annulez la modification dans la première session. Consultez les tables dans les deux sessions. Que se produit-il? 
```sql
--terminal 1
rollback;
```
Dans le terminal 1 rien n'a change vu qu'on a pas fait le commit dans le terminal 2, mais dans le terminal 2 dans la transaction le libelle a change'
#### 12. Validez dans la première session. Consultez les tables dans les deux sessions. Que se produit-il? 
```sql
--terminal 1
commit;
```
Les update c'est font a la suite et donc la dernier transaction valide' sera celle qui perdurera
#### 13. Dans l’un des 2 sessions, vider le contenu de la table Departement (c’est un autocommit). 
```sql
truncate table departement cascade;
```
#### 14. Depuis la session 1, insérez le département <’C1’,’Info’> et depuis la session 2 Insérez un employé <01,‘Henri’,‘C1’>. Que se passe-t-il ? 
```sql
--terminal 1
begin transaction;
insert into departement values ('C1', 'info');
--terminal 2
begin transaction;
insert into employe values (01, 'Henri', 'C1');
```
Si on commit pas la premiere insertion on obtient une erreur car cela viole la contrainte de cle etrangere
#### 15. Annulez l’insertion dans la session 1. Que se passe-t-il dans la session 2? 
On obtient une erreur car cela viole la contrainte de cle etrangere
#### 16. Depuis la session 1, insérez le département <’C1’,’Info’> puis depuis la session 2 Insérez un employé <01,‘Henri’,‘C1’>. Consultez les deux tables depuis les deux sessions. 
```sql
--terminal 1
begin transaction;
insert into departement values ('C1', 'info');
commit;
--terminal 2
begin transaction;
insert into employe values (01, 'Henri', 'C1');
commit;
```
Si on commit tout se passe bien
#### 17. Depuis la session 1 supprimez le département C1. Que se passe-t-il ? 
```sql
delete from departement where did='C1';
```
On obtient une erreur car c1 est encore reference en employe'
#### 18. Ajoutez depuis la session 1 l’employé <02,‘Grégoire,‘C1’>. Validez la transaction. 
```sql
begin transaction;
insert into employe values (02, 'gregoire', 'C1');
commit;
```
#### 19. Depuis la session 1, modifiez le nom de l’employé 01 en Coleen, ne validez pas encore. Depuis la fenêtre 2, modifiez le nom de l’employé 02 en Camille, ne validez pas encore. Consultez les tables. Que se passe-t-il ? 
```sql
--terminal 1
begin transaction;
update employe set nom='Coleen' where eid=1;
--terminal 2
begin transaction;
update employe set nom='Camille' where eid=2;
```
Dans chaque transaction les changements on ete faits mais les transaction de l'autre terminal non

#### 20. Validez la session1, consultez la table. Validez la session 2, consultez la table. Consultez à nouveau la table dans la session 1. 
```sql
--terminal 1
commit;
```
Maintenant le changement de coleen est visible depuis la transaction dans le terminal 2.





