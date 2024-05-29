parent(shyam, ram).
parent(shyam, priya).
parent(ram, anil).
parent(ram, veena). 
parent(priya, amita).
parent(anil, anjali).

sibling(X, Y) :-
    parent(Z, X),
    parent(Z, Y),
    X \= Y.

grandparent(X, Y) :-
    parent(X, Z),
    parent(Z, Y).

:- initialization(main).
main :-
    write('Parent-child relationships:'), nl,
    forall(parent(X, Y), (write(X), write(' is a parent of '), write(Y), nl)),
    write('Sibling relationships:'), nl,
    forall(sibling(X, Y), (write(X), write(' is a sibling of '), write(Y), nl)),
    write('Grandparent relationships:'), nl,
    forall(grandparent(X, Y), (write(X), write(' is a grandparent of '), write(Y), nl)),
    halt.



#     This Prolog program represents a family tree and defines predicates to infer parent-child, sibling, and grandparent relationships. Let's break down each part of the program:

# Facts for Parent-Child Relationships:

# The parent/2 predicate defines facts about parent-child relationships. For example, parent(shyam, ram) indicates that Shyam is the parent of Ram.
# Rule for Sibling Relationships:

# The sibling/2 predicate defines a rule to infer sibling relationships. Two individuals are siblings if they share the same parent(s) but are not the same individual (X \= Y).
# Rule for Grandparent Relationships:

# The grandparent/2 predicate defines a rule to infer grandparent relationships. An individual is a grandparent of another individual if they are a parent of a parent of that individual.
# Initialization Predicate (main/0):

# The main/0 predicate is called when the program is initialized. It writes the parent-child, sibling, and grandparent relationships to the standard output.
# The forall/2 predicate is used to iterate over each solution of a given goal and execute a goal for each solution.
# halt Predicate:

# The halt predicate is used to terminate the Prolog program after the main goal has been executed.
# Explanation:

# This program demonstrates how Prolog can be used to define and infer family relationships using logical rules.
# It provides a simple framework for representing and querying familial connections, such as parent-child, sibling, and grandparent relationships.
# The program showcases Prolog's ability to perform inference based on the rules and facts defined in the knowledge base, making it suitable for tasks involving reasoning over structured data.




