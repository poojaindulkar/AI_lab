% Facts
on(floor, monkey).
on(floor, chair).
in(room, monkey).
in(room, chair).
in(room, banana).
at(ceiling, banana).
strong(monkey).

% Rules
grasp(monkey).
climb(monkey, chair) :- strong(monkey).

push(monkey, chair) :-
    strong(monkey).

under(banana, chair) :-
    push(monkey, chair).

canreach(banana, monkey) :-
    (at(floor, banana); at(ceiling, banana)),
    under(banana, chair),
    climb(monkey, chair).

canget(banana, monkey) :-
    canreach(banana, monkey),
    grasp(monkey).

% Main method
main :-
    (canget(banana, monkey) -> 
        write('The monkey can get the banana!'), nl
    ; 
        write('The monkey cannot get the banana.'), nl
    ).

% Query
:- main.



# This Prolog program represents a scenario commonly known as the "Monkey and Banana" problem, which is a classic puzzle in artificial intelligence and logic programming. Let's break down each part of the program:

# Facts:

# Facts provide basic information about the elements involved in the problem:
# on/2: Indicates what is on top of what (e.g., the monkey is on the floor and the banana is at the ceiling).
# in/2: Indicates what is in which location (e.g., the monkey and the chair are in the room).
# strong/1: Indicates whether the monkey is strong.
# Rules:

# Rules define actions or conditions based on the given facts:
# grasp/1: Indicates the ability of the monkey to grasp objects.
# climb/2: Specifies that the monkey can climb onto a chair if it is strong.
# push/2: Specifies that the monkey can push the chair if it is strong.
# under/2: Indicates that the banana is under the chair if the monkey pushes the chair.
# canreach/2: Specifies conditions under which the monkey can reach the banana.
# canget/2: Specifies conditions under which the monkey can get the banana.
# Main Method:

# The main/0 predicate is the entry point of the program. It checks whether the monkey can get the banana based on the defined rules and facts.
# If the monkey can get the banana (canget(banana, monkey) is true), it prints "The monkey can get the banana!".
# If the monkey cannot get the banana, it prints "The monkey cannot get the banana."
# Query:

# The :- main. directive executes the main/0 predicate when the program is loaded.
# Explanation:

# This program models a scenario where a monkey is trying to get a banana placed at the ceiling.
# It uses rules and facts to represent the actions the monkey can take, such as climbing on a chair, pushing the chair, and grasping objects.
# By defining conditions under which the monkey can reach and get the banana, the program provides a logical solution to the puzzle.
# Prolog's inference engine allows it to determine whether the monkey can achieve its goal based on the defined rules and facts, demonstrating the power of logic programming in problem-solving domains.