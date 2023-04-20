unit_of_compilation:
    list_of_namespace_definition

list_of_namespace_definition:
    namespace_definition
    namespace_definition namespace_definition
    EMPTY

namespace_definition:
    namespace identifier {  type_definition_list }

type_definition_list
    type_definition
    type_definition type_definition_list
    EMPTY

type_definition
    type_macro_definition
    datatype_definition
    interface_definition
    factory_definition

type_macro_definition
    type identifier: type_list;

datatype_definition
    data { property_definition_list }

property_definition_list
    dataType identifier;
    dataType identifier; property_definition_list
    EMPTY

interface_definition
    interface identifier { function_definition_list }

function_definition_list
    function_definition
    function_definition; function_definition_list
    EMPTY

function_definition
    type identifier(function_parameters_list) ;

function_parameters_list
    function_parameter
    function_parameter, function_parameters_list
    EMPTY

function_parameter
    type identifier

factory_definition
    factory < type_list > identifier (function_parameters_list) { statement_list }

type_list
    identifier
    identifier, type_list

statement_list
    statement
    statement; statement_list
    EMPTY

statement
    variable_declaration
    expression
    while_statement
    do_statement
    foreach_statement
    if_statement
    switch_statement
    statement_block
    break_statement
    return_statement
    throw_statement
    try_statement

while_statement
    while (expression) statement_block

do_statement
    do statement_block while (expression)

switch_statement
    switch { case_list optional_default }

case_list
    case_expression_list statement_block

case_expression_list
    case expression :
    case expression : case_expression_list

throw_statement
    throw
    throw literal_string
    throw (literal_string, literal_string)

optional_default
    default: statement_block
    EMPTY

try_statement
    try statement_block catch_list

catch_list
    catch statement_block
    catch string_literal statement_block
    catch statement_block catch_list
    catch string_literal statement_block catch_list

break_statement
    break

return_statement
    return expression
    return

if_statement
    if (expression) statement_block
    if (expression) statement_block else statement_block

foreach_statement
    foreach ( identifier_or_identifier_declaration in expression) statement_block

statement_block
    { statement_list }

variable_declaration
    var identifier_list = expression

identifier_list
    identifier
    identifier, identifier_list
    EMPTY

expression
    lambda_expression
    conditional_expression
    assignment_expression

lambda_expression
    (argument_list) => lambda_expression
    (argument_list) => statement_block
    logicalOr_or_nullCoalescing

conditional_expression
    logicalOr_or_nullCoalescing_expression ? conditional_expression: conditional_expression
    logicalOr_or_nullCoalescing_expression

assignment_expression
    logicalOr_or_nullCoalescing_expression = assignment_expression
    logicalOr_or_nullCoalescing_expression += assignment_expression
    logicalOr_or_nullCoalescing_expression -= assignment_expression
    logicalOr_or_nullCoalescing_expression **= assignment_expression
    logicalOr_or_nullCoalescing_expression *= assignment_expression
    logicalOr_or_nullCoalescing_expression /= assignment_expression
    logicalOr_or_nullCoalescing_expression %= assignment_expression
    logicalOr_or_nullCoalescing_expression <<= assignment_expression
    logicalOr_or_nullCoalescing_expression >>= assignment_expression
    logicalOr_or_nullCoalescing_expression &= assignment_expression
    logicalOr_or_nullCoalescing_expression |= assignment_expression
    logicalOr_or_nullCoalescing_expression ^= assignment_expression
    logicalOr_or_nullCoalescing_expression ||= assignment_expression
    logicalOr_or_nullCoalescing_expression &&= assignment_expression
    logicalOr_or_nullCoalescing_expression ??= assignment_expression
    logicalOr_or_nullCoalescing_expression

logicalOr_or_nullCoalescing_expression
    logical_and_expression || logicalOr_or_nullCoalescing_expression
    logical_and_expression ?? logicalOr_or_nullCoalescing_expression
    logical_and_expression

logical_and_expression
    bitwise_or_expression && bitwise_or_expression
    bitwise_or_expression

bitwise_or_expression
    bitwise_xor_expression | bitwise_or_expression
    bitwise_xor_expression

bitwise_xor_expression
    bitwise_and_expression ^ bitwise_xor_expression
    bitwise_and_expression

bitwise_and_expression
    equality_expression & bitwise_and_expression
    equality_expression

equality_expression
    comparison_expression == equality_expression
    comparison_expression != equality_expression
    comparison_expression

comparison_expression
    addition_expression > comparison_expression
    addition_expression >= comparison_expression
    addition_expression < comparison_expression
    addition_expression <= comparison_expression
    addition_expression

addition_expression
    multiplication_expression + addition_expression
    multiplication_expression - addition_expression
    multiplication_expression

multiplication_expression
    exponentiation_expression * multiplication_expression
    exponentiation_expression / multiplication_expression
    exponentiation_expression % multiplication_expression
    exponentiation_expression

exponentiation_expression
    prefix_unaryExpression ** exponentiation_expression
    prefix_unaryExpression

prefix_unaryExpression
    ! postfix_increment_decrement
    ~ postfix_increment_decrement
    + postfix_increment_decrement
    ++ postfix_increment_decrement
    -- postfix_increment_decrement
    postfix_increment_decrement

postfix_increment_decrement
    function_call_expression ++
    new_object_expression --
    new_object_expression

function_call_expression
    grouping_expression(expression_ist)
    new identifier (expression_list)
    grouping_expression[expression_list]
    grouping_expression ?. function_call_expression
    grouping_expression . function_call_expression

grouping_expression
    ( expression )
    literal_or_identifier

literal_or_identifier
    identifier
    numeric_literal
    boolean_literal
    string_literal
    data_literal
    null < identifier >

data_literal:
    < identifier > { property_assignment_list }
    { property_assignment_list }

property_assignment_list:
    identifier : expression, property_assignment_list
    identifier : expression

expression_list:
    expression, expression_list
    expression

string_literal
    quote string_expresion_list quote

string_expresion_list
    string_content { expresion } string_expresion_list
    string_content
