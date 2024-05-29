% Facts for family relationships
father(john, mike).
father(john, lisa).
mother(mary, mike).
mother(mary, lisa).
brother(mike, lisa).
sister(lisa, mike).

% Facts for height (in cm)
height(john, 180).
height(mary, 165).
height(mike, 170).
height(lisa, 160).

% Rule to check if someone is a father
is_father(Father, Child) :-
    father(Father, Child).

% Rule to check if someone is a mother
is_mother(Mother, Child) :-
    mother(Mother, Child).

% Rule to check if someone is a brother
is_brother(Brother, Sibling) :-
    brother(Brother, Sibling).

% Rule to check if someone is a sister
is_sister(Sister, Sibling) :-
    sister(Sister, Sibling).

% Rule to check who is taller
is_taller(Person1, Person2) :-
    height(Person1, Height1),
    height(Person2, Height2),
    Height1 > Height2.

check_taller :-
    write('Enter the name of the first person: '),
    read(Person1),
    write('Enter the name of the second person: '),
    read(Person2),
    (is_taller(Person1, Person2) ->
        format('~w is taller than ~w.~n', [Person1, Person2]);
        format('~w is not taller than ~w.~n', [Person1, Person2])).

% Load the Prolog file
%?- ['family_tree.pl'].

% Check if John is the father of Mike
%?- is_father(john, mike).

% Check if Mary is the mother of Lisa
%?- is_mother(mary, lisa).

% Check if Mike is the brother of Lisa
%?- is_brother(mike, lisa).

% Check if Lisa is the sister of Mike
%?- is_sister(lisa, mike).

% Check if John is taller than Mary
%?- is_taller(john, mary).

% Check if Mike is taller than Lisa
%?- is_taller(mike, lisa).
%?- check_taller.
%Enter the name of the first person: mary.
%Enter the name of the second person: |: john.
%mary is not taller than john.
%true.




# This Prolog program represents a family tree and includes facts about family relationships and heights, as well as rules to check various relationships and heights among family members. Let's break down each part of the program:

# Facts for Family Relationships:

# The program defines facts about family relationships such as father, mother, brother, and sister. For example, father(john, mike) indicates that John is the father of Mike.
# Facts for Heights:

# The program defines facts about the height of family members. For example, height(john, 180) indicates that John is 180 cm tall.
# Rules for Checking Relationships:

# The program defines rules to check if someone is a father, mother, brother, or sister based on the provided facts.
# Rule for Checking Height:

# The program defines a rule is_taller/2 to check who is taller between two people. It retrieves the heights of the two people using the height/2 predicate and compares them.
# Predicate for User Interaction:

# The check_taller/0 predicate allows the user to input two people's names and checks who is taller among them using the is_taller/2 rule.
# Loading the Program:

# The %?- ['family_tree.pl']. line is a query to load the Prolog file containing the program.
# Queries:

# Queries are provided to check various relationships and heights among family members. For example:
# %?- is_father(john, mike).: This query checks if John is the father of Mike.
# %?- is_taller(john, mary).: This query checks if John is taller than Mary.
# %?- check_taller.: This query allows the user to input two people's names and check who is taller among them interactively.
# Explanation:

# This program demonstrates how Prolog can be used to represent and query relationships and attributes within a family tree.
# It provides a simple framework for checking relationships (father, mother, brother, sister) and comparing heights among family members.
# The program showcases Prolog's capabilities in defining rules and querying facts interactively, making it suitable for tasks involving knowledge representation and reasoning.