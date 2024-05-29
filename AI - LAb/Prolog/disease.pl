% Facts for diseases (name, type, symptom)
disease(flu, viral, fever).
disease(flu, viral, cough).
disease(common_cold, viral, sneezing).
disease(common_cold, viral, cough).
disease(malaria, parasitic, fever).
disease(malaria, parasitic, chills).
disease(diabetes, chronic, increased_thirst).
disease(diabetes, chronic, frequent_urination).
disease(cancer, chronic, unexplained_weight_loss).

% Facts for contagious diseases
contagious(flu).
contagious(common_cold).

% Rule to check if a disease is curable (diseases other than cancer are considered curable)
is_curable(Disease) :-
    Disease \= cancer.

% Rule to identify a disease based on symptom and type
identify_disease(Symptom, Type, Disease) :-
    disease(Disease, Type, Symptom).

% Rule to check if a disease is contagious
is_contagious(Disease) :-
    contagious(Disease).

% Rule to find diseases by type
disease_by_type(Type, Disease) :-
    disease(Disease, Type, _).

% Predicate to take input and identify a disease
diagnose_disease :-
    write('Enter the symptom: '),
    read(Symptom),
    write('Enter the type: '),
    read(Type),
    (identify_disease(Symptom, Type, Disease) ->
        format('The disease with symptom ~w and type ~w is ~w.~n', [Symptom, Type, Disease]);
        write('No disease found with the given symptom and type.~n')).

% Predicate to check if a disease is curable based on user input
check_curable :-
    write('Enter the name of the disease: '),
    read(Disease),
    (is_curable(Disease) ->
        format('The disease ~w is curable.~n', [Disease]);
        format('The disease ~w is not curable.~n', [Disease])).


% Load the Prolog file
%?- ['disease_diagnosis.pl'].

% Check if a disease is curable
%?- check_curable.

% Identify a disease based on symptom and type
%?- diagnose_disease.

% Check if a disease is contagious
%?- is_contagious(flu).

% Find diseases by type (e.g., viral)
%?- disease_by_type(viral, Disease).



# This Prolog program represents a simple knowledge base for diseases, their types, symptoms, and whether they are contagious or curable. Let's break down each part of the program:

# 1. **Facts for Diseases**:
#    - The `disease/3` predicate defines facts about diseases. Each fact has three arguments: name, type, and symptom(s).
#    - For example, `disease(flu, viral, fever)` indicates that flu is a viral disease with a symptom of fever.

# 2. **Facts for Contagious Diseases**:
#    - The `contagious/1` predicate lists diseases that are contagious. It indicates which diseases can be transmitted from one person to another.

# 3. **Rules for Curability**:
#    - The `is_curable/1` predicate defines a rule to check if a disease is curable. All diseases except cancer are considered curable.

# 4. **Rule for Identifying Diseases**:
#    - The `identify_disease/3` predicate defines a rule to identify a disease based on a given symptom and type. It checks if there is a disease with the specified symptom and type.

# 5. **Rule for Checking Contagiousness**:
#    - The `is_contagious/1` predicate defines a rule to check if a given disease is contagious. It simply checks if the disease is listed in the `contagious/1` predicate.

# 6. **Predicate for Diagnosing Diseases**:
#    - The `diagnose_disease/0` predicate takes input from the user (symptom and type) and identifies a disease based on the provided information.

# 7. **Predicate for Checking Curability**:
#    - The `check_curable/0` predicate takes input from the user (disease name) and checks if the disease is curable.

# 8. **Loading the Program**:
#    - The `%?- ['disease_diagnosis.pl'].` line is a query to load the Prolog file containing the program.

# 9. **Queries**:
#    - `%?- check_curable.`: This query checks if a given disease is curable based on user input.
#    - `%?- diagnose_disease.`: This query identifies a disease based on the symptom and type provided by the user.
#    - `%?- is_contagious(flu).`: This query checks if the flu is contagious.
#    - `%?- disease_by_type(viral, Disease).`: This query finds diseases of a specific type (e.g., viral).

# **Explanation**:
# - This program demonstrates basic Prolog concepts such as facts, rules, predicates, and queries.
# - It provides a simple framework for diagnosing diseases, checking their curability, and determining if they are contagious based on user input.
# - The program showcases how Prolog can be used to represent and query a knowledge base, making it suitable for rule-based systems like expert systems and decision support systems.
