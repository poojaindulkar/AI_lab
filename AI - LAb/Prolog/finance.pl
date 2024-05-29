% Define dynamic predicates for balance and transactions
:- dynamic(balance/1).
:- dynamic(income/2).
:- dynamic(expense/2).

% Initialize balance
initialize_balance(InitialBalance) :-
    assertz(balance(InitialBalance)).

% Add income
add_income(Description, Amount) :-
    balance(Balance),
    NewBalance is Balance + Amount,
    retract(balance(Balance)),
    assertz(balance(NewBalance)),
    assertz(income(Description, Amount)),
    write('Income added. New balance: $'), write(NewBalance), nl.

% Add expense
add_expense(Description, Amount) :-
    balance(Balance),
    NewBalance is Balance - Amount,
    retract(balance(Balance)),
    assertz(balance(NewBalance)),
    assertz(expense(Description, Amount)),
    write('Expense added. New balance: $'), write(NewBalance), nl.

% View balance
view_balance :-
    balance(Balance),
    write('Current balance: $'), write(Balance), nl.

% View transaction history
view_transactions :-
    write('Transaction History:'), nl,
    findall(income(Description, Amount), income(Description, Amount), IncomeList),
    findall(expense(Description, Amount), expense(Description, Amount), ExpenseList),
    print_transactions(IncomeList),
    print_transactions(ExpenseList).

print_transactions([]).
print_transactions([income(Description, Amount) | T]) :-
    write('Income: '), write(Description), write(', Amount: $'), write(Amount), nl,
    print_transactions(T).
print_transactions([expense(Description, Amount) | T]) :-
    write('Expense: '), write(Description), write(', Amount: $'), write(Amount), nl,
    print_transactions(T).

% Entry point for finance management
start_finance_management :-
    write('Welcome to Finance Management System.'), nl,
    write('Enter the initial balance: $'),
    read(InitialBalance),
    initialize_balance(InitialBalance),
    repeat,
    write('Choose an option:'), nl,
    write('1. Add income'), nl,
    write('2. Add expense'), nl,
    write('3. View balance'), nl,
    write('4. View transaction history'), nl,
    write('5. Exit'), nl,
    read(Option),
    process_option(Option),
    Option = 5,
    !.

process_option(1) :-
    write('Enter income description: '),
    read(Description),
    write('Enter income amount: $'),
    read(IncomeAmount),
    add_income(Description, IncomeAmount).

process_option(2) :-
    write('Enter expense description: '),
    read(Description),
    write('Enter expense amount: $'),
    read(ExpenseAmount),
    add_expense(Description, ExpenseAmount).

process_option(3) :-
    view_balance.

process_option(4) :-
    view_transactions.

process_option(5) :-
    write('Exiting Finance Management System.'), nl.

process_option(_) :-
    write('Invalid option. Please choose a valid option.'), nl.

% Run the finance management system
:- initialization(start_finance_management).





# This Prolog program implements a simple finance management system. It allows users to track their income, expenses, and overall balance. Let's break down each part of the program:

# Dynamic Predicates:

# balance/1, income/2, and expense/2 are dynamic predicates that can be modified during program execution.
# Initialization Predicate:

# initialize_balance/1 initializes the balance with the provided initial amount.
# Income and Expense Management:

# add_income/2 and add_expense/2 predicates add income and expenses respectively. They update the balance accordingly and assert income or expense transactions.
# View Balance and Transactions:

# view_balance/0 displays the current balance.
# view_transactions/0 displays the transaction history, including both income and expense transactions.
# User Interface:

# start_finance_management/0 is the entry point for the finance management system. It initializes the balance, provides a menu for users to choose options, and processes user inputs.
# process_option/1 handles user-selected options and executes corresponding actions.
# Printing Transactions:

# print_transactions/1 recursively prints income and expense transactions.
# Initialization:

# The :- initialization(start_finance_management). directive initializes the finance management system when the program is loaded.
# Explanation:

# This program provides a basic framework for managing personal finances, allowing users to track income, expenses, and balance.
# Users can interactively add income, add expenses, view their current balance, and see their transaction history.
# Dynamic predicates are used to maintain and update financial data during program execution.
# The user interface guides users through the finance management process, ensuring ease of use.
# Prolog's backtracking mechanism enables looping over the menu until the user chooses to exit, providing a seamless user experience.




