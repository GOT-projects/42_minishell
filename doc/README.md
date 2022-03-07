mini_shell

# TODO

fix path ~
wildcard

cat /dev/urandom | head -c 10

var _ unset au deb et set pour exec

# git

- merge master

```sh
git checkout master
git merge <branch>
```

- recup master

```sh
git checkout <branch>
git rebase master
```

# Documentation

https://www.gnu.org/savannah-checkouts/gnu/bash/manual/bash.html

https://www.gnu.org/software/bash/manual/bash.html

https://stackoverflow.com/questions/39199299/what-is-the-essential-difference-between-compound-command-and-normal-command-in

https://tiswww.case.edu/php/chet/readline/readline.html

https://stackoverflow.com/questions/55668865/how-to-kill-all-child-processes-after-parent-process-termination

https://stackoverflow.com/questions/48358121/c-fork-and-kill-at-the-same-time-not-working

## 2 Definitions
These definitions are used throughout the remainder of this manual.

`POSIX`
A family of open system standards based on Unix. Bash is primarily concerned with the Shell and Utilities portion of the POSIX 1003.1 standard.

`blank`
A space or tab character.

`builtin`
A command that is implemented internally by the shell itself, rather than by an executable program somewhere in the file system.

`control operator`
A token that performs a control function. It is a newline or one of the following: ‘||’, ‘&&’, ‘&’, ‘;’, ‘;;’, ‘;&’, ‘;;&’, ‘|’, ‘|&’, ‘(’, or ‘)’.

`exit status`
The value returned by a command to its caller. The value is restricted to eight bits, so the maximum value is 255.

`field`
A unit of text that is the result of one of the shell expansions. After expansion, when executing a command, the resulting fields are used as the command name and arguments.

`filename`
A string of characters used to identify a file.

`job`
A set of processes comprising a pipeline, and any processes descended from it, that are all in the same process group.

`job control`
A mechanism by which users can selectively stop (suspend) and restart (resume) execution of processes.

`metacharacter`
A character that, when unquoted, separates words. A metacharacter is a space, tab, newline, or one of the following characters: ‘|’, ‘&’, ‘;’, ‘(’, ‘)’, ‘<’, or ‘>’.

`name`
A word consisting solely of letters, numbers, and underscores, and beginning with a letter or underscore. Names are used as shell variable and function names. Also referred to as an identifier.

`operator`
A control operator or a redirection operator. See Redirections, for a list of redirection operators. Operators contain at least one unquoted metacharacter.

`process group`
A collection of related processes each having the same process group ID.

`process group ID`
A unique identifier that represents a process group during its lifetime.

`reserved word`
A word that has a special meaning to the shell. Most reserved words introduce shell flow control constructs, such as for and while.

`return status`
A synonym for exit status.

`signal`
A mechanism by which a process may be notified by the kernel of an event occurring in the system.

`special builtin`
A shell builtin command that has been classified as special by the POSIX standard.

`token`
A sequence of characters considered a single unit by the shell. It is either a word or an operator.

`word`
A sequence of characters treated as a unit by the shell. Words may not include unquoted metacharacters.

### 3.1.1 Shell Operation
The following is a brief description of the shell’s operation when it reads and executes a command. Basically, the shell does the following:

1. Reads its input from a file (see Shell Scripts), from a string supplied as an argument to the -c invocation option (see Invoking Bash), or from the user’s terminal.
2. Breaks the input into words and operators, obeying the quoting rules described in  Quoting. These tokens are separated by metacharacters. Alias expansion is performed by this step (see Aliases).
3. Parses the tokens into simple and compound commands (see Shell Commands).
4. Performs the various shell expansions (see Shell Expansions), breaking the expanded tokens into lists of filenames (see Filename Expansion) and commands and arguments.
5. Performs any necessary redirections (see Redirections) and removes the redirection operators and their operands from the argument list.
6. Executes the command (see Executing Commands).
7. Optionally waits for the command to complete and collects its exit status (see Exit Status).

### 3.1.2.2 Single Quotes
Enclosing characters in single quotes (‘'’) preserves the literal value of each character within the quotes. A single quote may not occur between single quotes, even when preceded by a backslash.

### 3.1.2.3 Double Quotes
Enclosing characters in double quotes (‘\"’) preserves the literal value of all characters within the quotes, with the exception of ‘\$’, ‘\`’, ‘\\’, and, when history expansion is enabled, ‘\!’. When the shell is in POSIX mode (see Bash POSIX Mode), the ‘\!’ has no special meaning within double quotes, even when history expansion is enabled. The characters ‘\$’ and ‘\`’ retain their special meaning within double quotes (see Shell Expansions). The backslash retains its special meaning only when followed by one of the following characters: ‘\$’, ‘\`’, ‘\"’, ‘\\’, or newline. Within double quotes, backslashes that are followed by one of these characters are removed. Backslashes preceding characters without a special meaning are left unmodified. A double quote may be quoted within double quotes by preceding it with a backslash. If enabled, history expansion will be performed unless an ‘\!’ appearing in double quotes is escaped using a backslash. The backslash preceding the ‘\!’ is not removed.

The special parameters ‘\*’ and ‘\@’ have special meaning when in double quotes (see Shell Parameter Expansion).

### 3.2.1 Reserved Words
Reserved words are words that have special meaning to the shell. They are used to begin and end the shell’s compound commands.

The following words are recognized as reserved when unquoted and the first word of a command (see below for exceptions):

if then elif else fi time for in until while do done case esac coproc select function { } \[[ ]] !

in is recognized as a reserved word if it is the third word of a case or select command. in and do are recognized as reserved words if they are the third word in a for command.

### 3.2.2 Simple Commands
A simple command is the kind of command encountered most often. It’s just a sequence of words separated by blanks, terminated by one of the shell’s control operators (see Definitions). The first word generally specifies a command to be executed, with the rest of the words being that command’s arguments.

The return status (see Exit Status) of a simple command is its exit status as provided by the POSIX 1003.1 waitpid function, or 128+n if the command was terminated by signal n.

### 3.2.3 Pipelines
A pipeline is a sequence of one or more commands separated by one of the control operators ‘|’ or ‘|&’.

The format for a pipeline is
```bash
[time [-p]] [!] command1 [ | or |& command2 ] …
```
The output of each command in the pipeline is connected via a pipe to the input of the next command. That is, each command reads the previous command’s output. This connection is performed before any redirections specified by the command.

If ‘|&’ is used, command1’s standard error, in addition to its standard output, is connected to command2’s standard input through the pipe; it is shorthand for 2>&1 |. This implicit redirection of the standard error to the standard output is performed after any redirections specified by the command.

The reserved word time causes timing statistics to be printed for the pipeline once it finishes. The statistics currently consist of elapsed (wall-clock) time and user and system time consumed by the command’s execution. The -p option changes the output format to that specified by POSIX. When the shell is in POSIX mode (see Bash POSIX Mode), it does not recognize time as a reserved word if the next token begins with a ‘-’. The TIMEFORMAT variable may be set to a format string that specifies how the timing information should be displayed. See Bash Variables, for a description of the available formats. The use of time as a reserved word permits the timing of shell builtins, shell functions, and pipelines. An external time command cannot time these easily.

When the shell is in POSIX mode (see Bash POSIX Mode), time may be followed by a newline. In this case, the shell displays the total user and system time consumed by the shell and its children. The TIMEFORMAT variable may be used to specify the format of the time information.

If the pipeline is not executed asynchronously (see Lists), the shell waits for all commands in the pipeline to complete.

Each command in a pipeline is executed in its own subshell, which is a separate process (see Command Execution Environment). If the lastpipe option is enabled using the shopt builtin (see The Shopt Builtin), the last element of a pipeline may be run by the shell process.

The exit status of a pipeline is the exit status of the last command in the pipeline, unless the pipefail option is enabled (see The Set Builtin). If pipefail is enabled, the pipeline’s return status is the value of the last (rightmost) command to exit with a non-zero status, or zero if all commands exit successfully. If the reserved word ‘!’ precedes the pipeline, the exit status is the logical negation of the exit status as described above. The shell waits for all commands in the pipeline to terminate before returning a value.

### 3.2.4 Lists of Commands
A list is a sequence of one or more pipelines separated by one of the operators ‘;’, ‘&’, ‘&&’, or ‘||’, and optionally terminated by one of ‘;’, ‘&’, or a newline.

Of these list operators, ‘&&’ and ‘||’ have equal precedence, followed by ‘;’ and ‘&’, which have equal precedence.

A sequence of one or more newlines may appear in a list to delimit commands, equivalent to a semicolon.

If a command is terminated by the control operator ‘&’, the shell executes the command asynchronously in a subshell. This is known as executing the command in the background, and these are referred to as asynchronous commands. The shell does not wait for the command to finish, and the return status is 0 (true). When job control is not active (see Job Control), the standard input for asynchronous commands, in the absence of any explicit redirections, is redirected from /dev/null.

Commands separated by a ‘;’ are executed sequentially; the shell waits for each command to terminate in turn. The return status is the exit status of the last command executed.

AND and OR lists are sequences of one or more pipelines separated by the control operators ‘&&’ and ‘||’, respectively. AND and OR lists are executed with left associativity.

An AND list has the form
```bash
command1 && command2
```
*command2* is executed if, and only if, *command1* returns an exit status of zero (success).

An OR list has the form
```bash
command1 || command2
```
*command2* is executed if, and only if, *command1* returns a non-zero exit status.

The return status of AND and OR lists is the exit status of the last command executed in the list.

### 3.2.5.3 Grouping Commands
Bash provides two ways to group a list of commands to be executed as a unit. When commands are grouped, redirections may be applied to the entire command list. For example, the output of all the commands in the list may be redirected to a single stream.

()
```bash
( list )
```
Placing a list of commands between parentheses causes a subshell environment to be created (see Command Execution Environment), and each of the commands in list to be executed in that subshell. Since the list is executed in a subshell, variable assignments do not remain in effect after the subshell completes.

{}
```bash
{ list; }
```
Placing a list of commands between curly braces causes the list to be executed in the current shell context. No subshell is created. The semicolon (or newline) following list is required.

In addition to the creation of a subshell, there is a subtle difference between these two constructs due to historical reasons. The braces are reserved words, so they must be separated from the list by blanks or other shell metacharacters. The parentheses are operators, and are recognized as separate tokens by the shell even if they are not separated from the list by whitespace.

The exit status of both of these constructs is the exit status of list.

### 3.2.6 Coprocesses

### 3.2.7 GNU Parallel

## 3.3 Shell Functions

Shell functions are a way to group commands for later execution using a single name for the group. They are executed just like a "regular" command. When the name of a shell function is used as a simple command name, the list of commands associated with that function name is executed. Shell functions are executed in the current shell context; no new process is created to interpret them.

Functions are declared using this syntax:
```bash
fname () compound-command [ redirections ]
```
or
```bash
function fname [()] compound-command [ redirections ]
```
This defines a shell function named fname. The reserved word function is optional. If the function reserved word is supplied, the parentheses are optional. The body of the function is the compound command compound-command (see Compound Commands). That command is usually a list enclosed between { and }, but may be any compound command listed above, with one exception: If the function reserved word is used, but the parentheses are not supplied, the braces are required. compound-command is executed whenever fname is specified as the name of a command. When the shell is in POSIX mode (see Bash POSIX Mode), fname must be a valid shell name and may not be the same as one of the special builtins (see Special Builtins). In default mode, a function name can be any unquoted shell word that does not contain ‘$’. Any redirections (see Redirections) associated with the shell function are performed when the function is executed. A function definition may be deleted using the -f option to the unset builtin (see Bourne Shell Builtins).

The exit status of a function definition is zero unless a syntax error occurs or a readonly function with the same name already exists. When executed, the exit status of a function is the exit status of the last command executed in the body.

Note that for historical reasons, in the most common usage the curly braces that surround the body of the function must be separated from the body by blanks or newlines. This is because the braces are reserved words and are only recognized as such when they are separated from the command list by whitespace or another shell metacharacter. Also, when using the braces, the list must be terminated by a semicolon, a ‘&’, or a newline.

When a function is executed, the arguments to the function become the positional parameters during its execution (see Positional Parameters). The special parameter ‘#’ that expands to the number of positional parameters is updated to reflect the change. Special parameter 0 is unchanged. The first element of the FUNCNAME variable is set to the name of the function while the function is executing.

All other aspects of the shell execution environment are identical between a function and its caller with these exceptions: the DEBUG and RETURN traps are not inherited unless the function has been given the trace attribute using the declare builtin or the -o functrace option has been enabled with the set builtin, (in which case all functions inherit the DEBUG and RETURN traps), and the ERR trap is not inherited unless the -o errtrace shell option has been enabled. See Bourne Shell Builtins, for the description of the trap builtin.

The FUNCNEST variable, if set to a numeric value greater than 0, defines a maximum function nesting level. Function invocations that exceed the limit cause the entire command to abort.

If the builtin command return is executed in a function, the function completes and execution resumes with the next command after the function call. Any command associated with the RETURN trap is executed before execution resumes. When a function completes, the values of the positional parameters and the special parameter ‘#’ are restored to the values they had prior to the function’s execution. If a numeric argument is given to return, that is the function’s return status; otherwise the function’s return status is the exit status of the last command executed before the return.

Variables local to the function may be declared with the local builtin. These variables are visible only to the function and the commands it invokes. This is particularly important when a shell function calls other functions.

Local variables "shadow" variables with the same name declared at previous scopes. For instance, a local variable declared in a function hides a global variable of the same name: references and assignments refer to the local variable, leaving the global variable unmodified. When the function returns, the global variable is once again visible.

The shell uses dynamic scoping to control a variable’s visibility within functions. With dynamic scoping, visible variables and their values are a result of the sequence of function calls that caused execution to reach the current function. The value of a variable that a function sees depends on its value within its caller, if any, whether that caller is the "global" scope or another shell function. This is also the value that a local variable declaration "shadows", and the value that is restored when the function returns.

For example, if a variable var is declared as local in function func1, and func1 calls another function func2, references to var made from within func2 will resolve to the local variable var from func1, shadowing any global variable named var.

The following script demonstrates this behavior. When executed, the script displays
```
In func2, var = func1 local
```
```bash
func1()
{
    local var='func1 local'
    func2
}

func2()
{
    echo "In func2, var = $var"
}

var=global
func1
```
The unset builtin also acts using the same dynamic scope: if a variable is local to the current scope, unset will unset it; otherwise the unset will refer to the variable found in any calling scope as described above. If a variable at the current local scope is unset, it will remain so until it is reset in that scope or until the function returns. Once the function returns, any instance of the variable at a previous scope will become visible. If the unset acts on a variable at a previous scope, any instance of a variable with that name that had been shadowed will become visible.

Function names and definitions may be listed with the -f option to the declare (typeset) builtin command (see Bash Builtins). The -F option to declare or typeset will list the function names only (and optionally the source file and line number, if the extdebug shell option is enabled). Functions may be exported so that subshells automatically have them defined with the -f option to the export builtin (see Bourne Shell Builtins).

Functions may be recursive. The FUNCNEST variable may be used to limit the depth of the function call stack and restrict the number of function invocations. By default, no limit is placed on the number of recursive calls.

### 3.4 Shell Parameters

A parameter is an entity that stores values. It can be a name, a number, or one of the special characters listed below. A variable is a parameter denoted by a name. A variable has a value and zero or more attributes. Attributes are assigned using the declare builtin command (see the description of the declare builtin in Bash Builtins).

A parameter is set if it has been assigned a value. The null string is a valid value. Once a variable is set, it may be unset only by using the unset builtin command.

A variable may be assigned to by a statement of the form
```
name=[value]
```
If value is not given, the variable is assigned the null string. All values undergo tilde expansion, parameter and variable expansion, command substitution, arithmetic expansion, and quote removal (detailed below). If the variable has its integer attribute set, then value is evaluated as an arithmetic expression even if the \$((…)) expansion is not used (see Arithmetic Expansion). Word splitting is not performed, with the exception of "\$@" as explained below. Filename expansion is not performed. Assignment statements may also appear as arguments to the alias, declare, typeset, export, readonly, and local builtin commands (declaration commands). When in POSIX mode (see Bash POSIX Mode), these builtins may appear in a command after one or more instances of the command builtin and retain these assignment statement properties.

In the context where an assignment statement is assigning a value to a shell variable or array index (see Arrays), the ‘+=’ operator can be used to append to or add to the variable’s previous value. This includes arguments to builtin commands such as declare that accept assignment statements (declaration commands). When ‘+=’ is applied to a variable for which the integer attribute has been set, value is evaluated as an arithmetic expression and added to the variable’s current value, which is also evaluated. When ‘+=’ is applied to an array variable using compound assignment (see Arrays), the variable’s value is not unset (as it is when using ‘=’), and new values are appended to the array beginning at one greater than the array’s maximum index (for indexed arrays), or added as additional key-value pairs in an associative array. When applied to a string-valued variable, value is expanded and appended to the variable’s value.

A variable can be assigned the nameref attribute using the -n option to the declare or local builtin commands (see Bash Builtins) to create a nameref, or a reference to another variable. This allows variables to be manipulated indirectly. Whenever the nameref variable is referenced, assigned to, unset, or has its attributes modified (other than using or changing the nameref attribute itself), the operation is actually performed on the variable specified by the nameref variable’s value. A nameref is commonly used within shell functions to refer to a variable whose name is passed as an argument to the function. For instance, if a variable name is passed to a shell function as its first argument, running
```
declare -n ref=$1
```
inside the function creates a nameref variable ref whose value is the variable name passed as the first argument. References and assignments to ref, and changes to its attributes, are treated as references, assignments, and attribute modifications to the variable whose name was passed as $1.

If the control variable in a for loop has the nameref attribute, the list of words can be a list of shell variables, and a name reference will be established for each word in the list, in turn, when the loop is executed. Array variables cannot be given the nameref attribute. However, nameref variables can reference array variables and subscripted array variables. Namerefs can be unset using the -n option to the unset builtin (see Bourne Shell Builtins). Otherwise, if unset is executed with the name of a nameref variable as an argument, the variable referenced by the nameref variable will be unset.

### 3.4.1 Positional Parameters

### 3.4.2 Special Parameters
The shell treats several parameters specially. These parameters may only be referenced; assignment to them is not allowed.

`*`
(\$*) Expands to the positional parameters, starting from one. When the expansion is not within double quotes, each positional parameter expands to a separate word. In contexts where it is performed, those words are subject to further word splitting and filename expansion. When the expansion occurs within double quotes, it expands to a single word with the value of each parameter separated by the first character of the IFS special variable. That is, "\$*" is equivalent to "\$1c\$2c…", where c is the first character of the value of the IFS variable. If IFS is unset, the parameters are separated by spaces. If IFS is null, the parameters are joined without intervening separators.

`@`
(\$@) Expands to the positional parameters, starting from one. In contexts where word splitting is performed, this expands each positional parameter to a separate word; if not within double quotes, these words are subject to word splitting. In contexts where word splitting is not performed, this expands to a single word with each positional parameter separated by a space. When the expansion occurs within double quotes, and word splitting is performed, each parameter expands to a separate word. That is, "\$@" is equivalent to "\$1" "\$2" …. If the double-quoted expansion occurs within a word, the expansion of the first parameter is joined with the beginning part of the original word, and the expansion of the last parameter is joined with the last part of the original word. When there are no positional parameters, "\$@" and \$@ expand to nothing (i.e., they are removed).

`#`
(\$#) Expands to the number of positional parameters in decimal.

`?`
(\$?) Expands to the exit status of the most recently executed foreground pipeline.

`-`
(\$-, a hyphen.) Expands to the current option flags as specified upon invocation, by the set builtin command, or those set by the shell itself (such as the -i option).

`$`
(\$\$) Expands to the process ID of the shell. In a () subshell, it expands to the process ID of the invoking shell, not the subshell.

`!`
(\$!) Expands to the process ID of the job most recently placed into the background, whether executed as an asynchronous command or using the bg builtin (see Job Control Builtins).

`0`
(\$0) Expands to the name of the shell or shell script. This is set at shell initialization. If Bash is invoked with a file of commands (see Shell Scripts), $0 is set to the name of that file. If Bash is started with the -c option (see Invoking Bash), then \$0 is set to the first argument after the string to be executed, if one is present. Otherwise, it is set to the filename used to invoke Bash, as given by argument zero.

## 3.5 Shell Expansions

### 3.5.1 Brace Expansion

### 3.5.2 Tilde Expansion
If a word begins with an unquoted tilde character (‘~’), all of the characters up to the first unquoted slash (or all characters, if there is no unquoted slash) are considered a tilde-prefix. If none of the characters in the tilde-prefix are quoted, the characters in the tilde-prefix following the tilde are treated as a possible login name. If this login name is the null string, the tilde is replaced with the value of the HOME shell variable. If HOME is unset, the home directory of the user executing the shell is substituted instead. Otherwise, the tilde-prefix is replaced with the home directory associated with the specified login name.

If the tilde-prefix is ‘~+’, the value of the shell variable PWD replaces the tilde-prefix. If the tilde-prefix is ‘~-’, the value of the shell variable OLDPWD, if it is set, is substituted.

If the characters following the tilde in the tilde-prefix consist of a number N, optionally prefixed by a ‘+’ or a ‘-’, the tilde-prefix is replaced with the corresponding element from the directory stack, as it would be displayed by the dirs builtin invoked with the characters following tilde in the tilde-prefix as an argument (see The Directory Stack). If the tilde-prefix, sans the tilde, consists of a number without a leading ‘+’ or ‘-’, ‘+’ is assumed.

If the login name is invalid, or the tilde expansion fails, the word is left unchanged.

Each variable assignment is checked for unquoted tilde-prefixes immediately following a ‘:’ or the first ‘=’. In these cases, tilde expansion is also performed. Consequently, one may use filenames with tildes in assignments to PATH, MAILPATH, and CDPATH, and the shell assigns the expanded value.

The following table shows how Bash treats unquoted tilde-prefixes:

~
The value of $HOME

~/foo
$HOME/foo

~fred/foo
The subdirectory foo of the home directory of the user fred

~+/foo
$PWD/foo

~-/foo
${OLDPWD-'~-'}/foo

~N
The string that would be displayed by ‘dirs +N’

~+N
The string that would be displayed by ‘dirs +N’

~-N
The string that would be displayed by ‘dirs -N’

Bash also performs tilde expansion on words satisfying the conditions of variable assignments (see Shell Parameters) when they appear as arguments to simple commands. Bash does not do this, except for the declaration commands listed above, when in POSIX mode.

### 3.5.3 Shell Parameter Expansion

### 3.5.4 Command Substitution
Command substitution allows the output of a command to replace the command itself. Command substitution occurs when a command is enclosed as follows:
```bash
$(command)
```
or
```bash
`command`
```
Bash performs the expansion by executing command in a subshell environment and replacing the command substitution with the standard output of the command, with any trailing newlines deleted. Embedded newlines are not deleted, but they may be removed during word splitting. The command substitution \$(cat file) can be replaced by the equivalent but faster \$(< file).

When the old-style backquote form of substitution is used, backslash retains its literal meaning except when followed by ‘\$’, ‘`’, or ‘\’. The first backquote not preceded by a backslash terminates the command substitution. When using the \$(command) form, all characters between the parentheses make up the command; none are treated specially.

Command substitutions may be nested. To nest when using the backquoted form, escape the inner backquotes with backslashes.

If the substitution appears within double quotes, word splitting and filename expansion are not performed on the results.

### 3.5.5 Arithmetic Expansion
Arithmetic expansion allows the evaluation of an arithmetic expression and the substitution of the result. The format for arithmetic expansion is:
```bash
$(( expression ))
```
The expression is treated as if it were within double quotes, but a double quote inside the parentheses is not treated specially. All tokens in the expression undergo parameter and variable expansion, command substitution, and quote removal. The result is treated as the arithmetic expression to be evaluated. Arithmetic expansions may be nested.

The evaluation is performed according to the rules listed below (see Shell Arithmetic). If the expression is invalid, Bash prints a message indicating failure to the standard error and no substitution occurs.

### 3.5.6 Process Substitution

### 3.5.7 Word Splitting

### 3.5.8 Filename Expansion

### 3.5.8.1 Pattern Matching

### 3.5.9 Quote Removal
After the preceding expansions, all unquoted occurrences of the characters ‘\’, ‘'’, and ‘"’ that did not result from one of the above expansions are removed.

## 3.6 Redirections
Before a command is executed, its input and output may be redirected using a special notation interpreted by the shell. Redirection allows commands’ file handles to be duplicated, opened, closed, made to refer to different files, and can change the files the command reads from and writes to. Redirection may also be used to modify file handles in the current shell execution environment. The following redirection operators may precede or appear anywhere within a simple command or may follow a command. Redirections are processed in the order they appear, from left to right.

Each redirection that may be preceded by a file descriptor number may instead be preceded by a word of the form {varname}. In this case, for each redirection operator except >&- and <&-, the shell will allocate a file descriptor greater than 10 and assign it to {varname}. If >&- or <&- is preceded by {varname}, the value of varname defines the file descriptor to close. If {varname} is supplied, the redirection persists beyond the scope of the command, allowing the shell programmer to manage the file descriptor’s lifetime manually.

In the following descriptions, if the file descriptor number is omitted, and the first character of the redirection operator is ‘<’, the redirection refers to the standard input (file descriptor 0). If the first character of the redirection operator is ‘>’, the redirection refers to the standard output (file descriptor 1).

The word following the redirection operator in the following descriptions, unless otherwise noted, is subjected to brace expansion, tilde expansion, parameter expansion, command substitution, arithmetic expansion, quote removal, filename expansion, and word splitting. If it expands to more than one word, Bash reports an error.

Note that the order of redirections is significant. For example, the command
```bash
ls > dirlist 2>&1
```
directs both standard output (file descriptor 1) and standard error (file descriptor 2) to the file dirlist, while the command
```bash
ls 2>&1 > dirlist
```
directs only the standard output to file dirlist, because the standard error was made a copy of the standard output before the standard output was redirected to dirlist.

Bash handles several filenames specially when they are used in redirections, as described in the following table. If the operating system on which Bash is running provides these special files, bash will use them; otherwise it will emulate them internally with the behavior described below.

`/dev/fd/fd`
If fd is a valid integer, file descriptor fd is duplicated.

`/dev/stdin`
File descriptor 0 is duplicated.

`/dev/stdout`
File descriptor 1 is duplicated.

`/dev/stderr`
File descriptor 2 is duplicated.

`/dev/tcp/host/port`
If host is a valid hostname or Internet address, and port is an integer port number or service name, Bash attempts to open the corresponding TCP socket.

`/dev/udp/host/port`
If host is a valid hostname or Internet address, and port is an integer port number or service name, Bash attempts to open the corresponding UDP socket.

A failure to open or create a file causes the redirection to fail.

Redirections using file descriptors greater than 9 should be used with care, as they may conflict with file descriptors the shell uses internally.

### 3.6.1 Redirecting Input
Redirection of input causes the file whose name results from the expansion of word to be opened for reading on file descriptor n, or the standard input (file descriptor 0) if n is not specified.

The general format for redirecting input is:
```bash
[n]<word
```
### 3.6.2 Redirecting Output
Redirection of output causes the file whose name results from the expansion of word to be opened for writing on file descriptor n, or the standard output (file descriptor 1) if n is not specified. If the file does not exist it is created; if it does exist it is truncated to zero size.

The general format for redirecting output is:
```bash
[n]>[|]word
```
If the redirection operator is ‘>’, and the noclobber option to the set builtin has been enabled, the redirection will fail if the file whose name results from the expansion of word exists and is a regular file. If the redirection operator is ‘>|’, or the redirection operator is ‘>’ and the noclobber option is not enabled, the redirection is attempted even if the file named by word exists.

### 3.6.3 Appending Redirected Output
Redirection of output in this fashion causes the file whose name results from the expansion of word to be opened for appending on file descriptor n, or the standard output (file descriptor 1) if n is not specified. If the file does not exist it is created.

The general format for appending output is:
```bash
[n]>>word
```

### 3.6.4 Redirecting Standard Output and Standard Error
This construct allows both the standard output (file descriptor 1) and the standard error output (file descriptor 2) to be redirected to the file whose name is the expansion of word.

There are two formats for redirecting standard output and standard error:
```bash
&>word
```
and
```bash
>&word
```
Of the two forms, the first is preferred. This is semantically equivalent to
```bash
>word 2>&1
```
When using the second form, word may not expand to a number or ‘-’. If it does, other redirection operators apply (see Duplicating File Descriptors below) for compatibility reasons.

### 3.6.5 Appending Standard Output and Standard Error
This construct allows both the standard output (file descriptor 1) and the standard error output (file descriptor 2) to be appended to the file whose name is the expansion of word.

The format for appending standard output and standard error is:
```bash
&>>word
```
This is semantically equivalent to
```bash
>>word 2>&1
```
(see Duplicating File Descriptors below).

### 3.6.6 Here Documents
This type of redirection instructs the shell to read input from the current source until a line containing only word (with no trailing blanks) is seen. All of the lines read up to that point are then used as the standard input (or file descriptor n if n is specified) for a command.

The format of here-documents is:
```bash
[n]<<[-]word
        here-document
delimiter
```
No parameter and variable expansion, command substitution, arithmetic expansion, or filename expansion is performed on word. If any part of word is quoted, the delimiter is the result of quote removal on word, and the lines in the here-document are not expanded. If word is unquoted, all lines of the here-document are subjected to parameter expansion, command substitution, and arithmetic expansion, the character sequence \newline is ignored, and ‘\’ must be used to quote the characters ‘\’, ‘\$’, and ‘`’.

If the redirection operator is ‘<<-’, then all leading tab characters are stripped from input lines and the line containing delimiter. This allows here-documents within shell scripts to be indented in a natural fashion.

### 3.6.7 Here Strings
A variant of here documents, the format is:
```bash
[n]<<< word
```
The word undergoes tilde expansion, parameter and variable expansion, command substitution, arithmetic expansion, and quote removal. Filename expansion and word splitting are not performed. The result is supplied as a single string, with a newline appended, to the command on its standard input (or file descriptor n if n is specified).

### 3.6.8 Duplicating File Descriptors

### 3.6.9 Moving File Descriptors

### 3.6.10 Opening File Descriptors for Reading and Writing

## 3.7 Executing Commands

### 3.7.1 Simple Command Expansion
When a simple command is executed, the shell performs the following expansions, assignments, and redirections, from left to right, in the following order.

1. The words that the parser has marked as variable assignments (those preceding the command name) and redirections are saved for later processing.
2. The words that are not variable assignments or redirections are expanded (see Shell Expansions). If any words remain after expansion, the first word is taken to be the name of the command and the remaining words are the arguments.
3. Redirections are performed as described above (see Redirections).
3. The text after the ‘=’ in each variable assignment undergoes tilde expansion, parameter expansion, command substitution, arithmetic expansion, and quote removal before being assigned to the variable.

If no command name results, the variable assignments affect the current shell environment. Otherwise, the variables are added to the environment of the executed command and do not affect the current shell environment. If any of the assignments attempts to assign a value to a readonly variable, an error occurs, and the command exits with a non-zero status.

If no command name results, redirections are performed, but do not affect the current shell environment. A redirection error causes the command to exit with a non-zero status.

If there is a command name left after expansion, execution proceeds as described below. Otherwise, the command exits. If one of the expansions contained a command substitution, the exit status of the command is the exit status of the last command substitution performed. If there were no command substitutions, the command exits with a status of zero.

### 3.7.2 Command Search and Execution
After a command has been split into words, if it results in a simple command and an optional list of arguments, the following actions are taken.

1. If the command name contains no slashes, the shell attempts to locate it. If there exists a shell function by that name, that function is invoked as described in Shell Functions.
2. If the name does not match a function, the shell searches for it in the list of shell builtins. If a match is found, that builtin is invoked.
3. If the name is neither a shell function nor a builtin, and contains no slashes, Bash searches each element of $PATH for a directory containing an executable file by that name. Bash uses a hash table to remember the full pathnames of executable files to avoid multiple PATH searches (see the description of hash in Bourne Shell Builtins). A full search of the directories in $PATH is performed only if the command is not found in the hash table. If the search is unsuccessful, the shell searches for a defined shell function named command_not_found_handle. If that function exists, it is invoked in a separate execution environment with the original command and the original command’s arguments as its arguments, and the function’s exit status becomes the exit status of that subshell. If that function is not defined, the shell prints an error message and returns an exit status of 127.
4. If the search is successful, or if the command name contains one or more slashes, the shell executes the named program in a separate execution environment. Argument 0 is set to the name given, and the remaining arguments to the command are set to the arguments supplied, if any.
5. If this execution fails because the file is not in executable format, and the file is not a directory, it is assumed to be a shell script and the shell executes it as described in Shell Scripts.
6. If the command was not begun asynchronously, the shell waits for the command to complete and collects its exit status.

### 3.7.3 Command Execution Environment
The shell has an execution environment, which consists of the following:

- open files inherited by the shell at invocation, as modified by redirections supplied to the exec builtin
- the current working directory as set by cd, pushd, or popd, or inherited by the shell at invocation
- the file creation mode mask as set by umask or inherited from the shell’s parent
- current traps set by trap
- shell parameters that are set by variable assignment or with set or inherited from the shell’s parent in the environment
- shell functions defined during execution or inherited from the shell’s parent in the environment
- options enabled at invocation (either by default or with command-line arguments) or by set
- options enabled by shopt (see The Shopt Builtin)
- shell aliases defined with alias (see Aliases)
- various process IDs, including those of background jobs (see Lists), the value of $$, and the value of $PPID

When a simple command other than a builtin or shell function is to be executed, it is invoked in a separate execution environment that consists of the following. Unless otherwise noted, the values are inherited from the shell.

- the shell’s open files, plus any modifications and additions specified by redirections to the command
- the current working directory
- the file creation mode mask
- shell variables and functions marked for export, along with variables exported for the command, passed in the environment (see Environment)
- traps caught by the shell are reset to the values inherited from the shell’s parent, and traps ignored by the shell are ignored

A command invoked in this separate environment cannot affect the shell’s execution environment.

Command substitution, commands grouped with parentheses, and asynchronous commands are invoked in a subshell environment that is a duplicate of the shell environment, except that traps caught by the shell are reset to the values that the shell inherited from its parent at invocation. Builtin commands that are invoked as part of a pipeline are also executed in a subshell environment. Changes made to the subshell environment cannot affect the shell’s execution environment.

Subshells spawned to execute command substitutions inherit the value of the -e option from the parent shell. When not in POSIX mode, Bash clears the -e option in such subshells.

If a command is followed by a ‘&’ and job control is not active, the default standard input for the command is the empty file /dev/null. Otherwise, the invoked command inherits the file descriptors of the calling shell as modified by redirections.

### 3.7.4 Environment
When a program is invoked it is given an array of strings called the environment. This is a list of name-value pairs, of the form name=value.

Bash provides several ways to manipulate the environment. On invocation, the shell scans its own environment and creates a parameter for each name found, automatically marking it for export to child processes. Executed commands inherit the environment. The export and ‘declare -x’ commands allow parameters and functions to be added to and deleted from the environment. If the value of a parameter in the environment is modified, the new value becomes part of the environment, replacing the old. The environment inherited by any executed command consists of the shell’s initial environment, whose values may be modified in the shell, less any pairs removed by the unset and ‘export -n’ commands, plus any additions via the export and ‘declare -x’ commands.

The environment for any simple command or function may be augmented temporarily by prefixing it with parameter assignments, as described in Shell Parameters. These assignment statements affect only the environment seen by that command.

If the -k option is set (see The Set Builtin), then all parameter assignments are placed in the environment for a command, not just those that precede the command name.

When Bash invokes an external command, the variable ‘\$_’ is set to the full pathname of the command and passed to that command in its environment.

### 3.7.5 Exit Status
The exit status of an executed command is the value returned by the waitpid system call or equivalent function. Exit statuses fall between 0 and 255, though, as explained below, the shell may use values above 125 specially. Exit statuses from shell builtins and compound commands are also limited to this range. Under certain circumstances, the shell will use special values to indicate specific failure modes.

For the shell’s purposes, a command which exits with a zero exit status has succeeded. A non-zero exit status indicates failure. This seemingly counter-intuitive scheme is used so there is one well-defined way to indicate success and a variety of ways to indicate various failure modes. When a command terminates on a fatal signal whose number is N, Bash uses the value 128+N as the exit status.

If a command is not found, the child process created to execute it returns a status of 127. If a command is found but is not executable, the return status is 126.

If a command fails because of an error during expansion or redirection, the exit status is greater than zero.

The exit status is used by the Bash conditional commands (see Conditional Constructs) and some of the list constructs (see Lists).

All of the Bash builtins return an exit status of zero if they succeed and a non-zero status on failure, so they may be used by the conditional and list constructs. All builtins return an exit status of 2 to indicate incorrect usage, generally invalid options or missing arguments.

### 3.7.6 Signals
When Bash is interactive, in the absence of any traps, it ignores SIGTERM (so that ‘kill 0’ does not kill an interactive shell), and SIGINT is caught and handled (so that the wait builtin is interruptible). When Bash receives a SIGINT, it breaks out of any executing loops. In all cases, Bash ignores SIGQUIT. If job control is in effect (see Job Control), Bash ignores SIGTTIN, SIGTTOU, and SIGTSTP.

Non-builtin commands started by Bash have signal handlers set to the values inherited by the shell from its parent. When job control is not in effect, asynchronous commands ignore SIGINT and SIGQUIT in addition to these inherited handlers. Commands run as a result of command substitution ignore the keyboard-generated job control signals SIGTTIN, SIGTTOU, and SIGTSTP.

The shell exits by default upon receipt of a SIGHUP. Before exiting, an interactive shell resends the SIGHUP to all jobs, running or stopped. Stopped jobs are sent SIGCONT to ensure that they receive the SIGHUP. To prevent the shell from sending the SIGHUP signal to a particular job, it should be removed from the jobs table with the disown builtin (see Job Control Builtins) or marked to not receive SIGHUP using disown -h.

If the huponexit shell option has been set with shopt (see The Shopt Builtin), Bash sends a SIGHUP to all jobs when an interactive login shell exits.

If Bash is waiting for a command to complete and receives a signal for which a trap has been set, the trap will not be executed until the command completes. When Bash is waiting for an asynchronous command via the wait builtin, the reception of a signal for which a trap has been set will cause the wait builtin to return immediately with an exit status greater than 128, immediately after which the trap is executed.

### 3.8 Shell Scripts

## 4 Shell Builtin Commands

Builtin commands are contained within the shell itself. When the name of a builtin command is used as the first word of a simple command (see Simple Commands), the shell executes the command directly, without invoking another program. Builtin commands are necessary to implement functionality impossible or inconvenient to obtain with separate utilities.

This section briefly describes the builtins which Bash inherits from the Bourne Shell, as well as the builtin commands which are unique to or have been extended in Bash.

Several builtin commands are described in other chapters: builtin commands which provide the Bash interface to the job control facilities (see Job Control Builtins), the directory stack (see Directory Stack Builtins), the command history (see Bash History Builtins), and the programmable completion facilities (see Programmable Completion Builtins).

Many of the builtins have been extended by POSIX or Bash.

Unless otherwise noted, each builtin command documented as accepting options preceded by ‘-’ accepts ‘--’ to signify the end of the options. The :, true, false, and test/[ builtins do not accept options and do not treat ‘--’ specially. The exit, logout, return, break, continue, let, and shift builtins accept and process arguments beginning with ‘-’ without requiring ‘--’. Other builtins that accept arguments but are not specified as accepting options interpret arguments beginning with ‘-’ as invalid options and require ‘--’ to prevent this interpretation.

### 4.1 Bourne Shell Builtins

...

`cd`
```bash
cd [-L|[-P [-e]] [-@] [directory]
```
Change the current working directory to directory. If directory is not supplied, the value of the HOME shell variable is used. Any additional arguments following directory are ignored. If the shell variable CDPATH exists, it is used as a search path: each directory name in CDPATH is searched for directory, with alternative directory names in CDPATH separated by a colon (‘:’). If directory begins with a slash, CDPATH is not used.

The -P option means to not follow symbolic links: symbolic links are resolved while cd is traversing directory and before processing an instance of ‘..’ in directory.

By default, or when the -L option is supplied, symbolic links in directory are resolved after cd processes an instance of ‘..’ in directory.

If ‘..’ appears in directory, it is processed by removing the immediately preceding pathname component, back to a slash or the beginning of directory.

If the -e option is supplied with -P and the current working directory cannot be successfully determined after a successful directory change, cd will return an unsuccessful status.

On systems that support it, the -@ option presents the extended attributes associated with a file as a directory.

If directory is ‘-’, it is converted to $OLDPWD before the directory change is attempted.

If a non-empty directory name from CDPATH is used, or if ‘-’ is the first argument, and the directory change is successful, the absolute pathname of the new working directory is written to the standard output.

The return status is zero if the directory is successfully changed, non-zero otherwise.

`exit`
```bash
exit [n]
```
Exit the shell, returning a status of n to the shell’s parent. If n is omitted, the exit status is that of the last command executed. Any trap on EXIT is executed before the shell terminates.

`export`
```bash
export [-fn] [-p] [name[=value]]
```
Mark each name to be passed to child processes in the environment. If the -f option is supplied, the names refer to shell functions; otherwise the names refer to shell variables. The -n option means to no longer mark each name for export. If no names are supplied, or if the -p option is given, a list of names of all exported variables is displayed. The -p option displays output in a form that may be reused as input. If a variable name is followed by =value, the value of the variable is set to value.

The return status is zero unless an invalid option is supplied, one of the names is not a valid shell variable name, or -f is supplied with a name that is not a shell function.

`pwd`
```bash
pwd [-LP]
```
Print the absolute pathname of the current working directory. If the -P option is supplied, the pathname printed will not contain symbolic links. If the -L option is supplied, the pathname printed may contain symbolic links. The return status is zero unless an error is encountered while determining the name of the current directory or an invalid option is supplied.

### 4.2 Bash Builtin Commands

`declare`
```bash
declare [-aAfFgiIlnrtux] [-p] [name[=value] …]
```
    `-a`
    Each name is an indexed array variable (see Arrays).

    `-A`
    Each name is an associative array variable (see Arrays).

    `-f`
    Use function names only.

    `-i`
    The variable is to be treated as an integer; arithmetic evaluation (see Shell Arithmetic) is performed when the variable is assigned a value.

    `-l`
    When the variable is assigned a value, all upper-case characters are converted to lower-case. The upper-case attribute is disabled.

    `-n`
    Give each name the nameref attribute, making it a name reference to another variable. That other variable is defined by the value of name. All references, assignments, and attribute modifications to name, except for those using or changing the -n attribute itself, are performed on the variable referenced by name’s value. The nameref attribute cannot be applied to array variables.

    `-r`
    Make names readonly. These names cannot then be assigned values by subsequent assignment statements or unset.

    `-t`
    Give each name the trace attribute. Traced functions inherit the DEBUG and RETURN traps from the calling shell. The trace attribute has no special meaning for variables.

    `-u`
    When the variable is assigned a value, all lower-case characters are converted to upper-case. The lower-case attribute is disabled.

    `-x`
    Mark each name for export to subsequent commands via the environment.

`echo`
```bash
echo [-neE] [arg …]
```
Output the args, separated by spaces, terminated with a newline. The return status is 0 unless a write error occurs. If -n is specified, the trailing newline is suppressed. If the -e option is given, interpretation of the following backslash-escaped characters is enabled. The -E option disables the interpretation of these escape characters, even on systems where they are interpreted by default. The xpg_echo shell option may be used to dynamically determine whether or not echo expands these escape characters by default. echo does not interpret -- to mean the end of options.

## 4.3 Modifying Shell Behavior

### 4.3.1 The Set Builtin

### 4.3.2 The Shopt Builtin

## 5 Shell Variables

## 5.1 Bourne Shell Variables

### 5.2 Bash Variables
These variables are set or used by Bash, but other shells do not normally treat them specially.

A few variables used by Bash are described in different chapters: variables for controlling the job control facilities (see Job Control Variables).

_
($_, an underscore.) At shell startup, set to the pathname used to invoke the shell or shell script being executed as passed in the environment or argument list. Subsequently, expands to the last argument to the previous simple command executed in the foreground, after expansion. Also set to the full pathname used to invoke each command executed and placed in the environment exported to that command. When checking mail, this parameter holds the name of the mail file.

BASH
The full pathname used to execute the current instance of Bash.

BASHOPTS
A colon-separated list of enabled shell options. Each word in the list is a valid argument for the -s option to the shopt builtin command (see The Shopt Builtin). The options appearing in BASHOPTS are those reported as ‘on’ by ‘shopt’. If this variable is in the environment when Bash starts up, each shell option in the list will be enabled before reading any startup files. This variable is readonly.

BASHPID
Expands to the process ID of the current Bash process. This differs from $$ under certain circumstances, such as subshells that do not require Bash to be re-initialized. Assignments to BASHPID have no effect. If BASHPID is unset, it loses its special properties, even if it is subsequently reset.

BASH_ALIASES
An associative array variable whose members correspond to the internal list of aliases as maintained by the alias builtin. (see Bourne Shell Builtins). Elements added to this array appear in the alias list; however, unsetting array elements currently does not cause aliases to be removed from the alias list. If BASH_ALIASES is unset, it loses its special properties, even if it is subsequently reset.

BASH_ARGC
An array variable whose values are the number of parameters in each frame of the current bash execution call stack. The number of parameters to the current subroutine (shell function or script executed with . or source) is at the top of the stack. When a subroutine is executed, the number of parameters passed is pushed onto BASH_ARGC. The shell sets BASH_ARGC only when in extended debugging mode (see The Shopt Builtin for a description of the extdebug option to the shopt builtin). Setting extdebug after the shell has started to execute a script, or referencing this variable when extdebug is not set, may result in inconsistent values.

BASH_ARGV
An array variable containing all of the parameters in the current bash execution call stack. The final parameter of the last subroutine call is at the top of the stack; the first parameter of the initial call is at the bottom. When a subroutine is executed, the parameters supplied are pushed onto BASH_ARGV. The shell sets BASH_ARGV only when in extended debugging mode (see The Shopt Builtin for a description of the extdebug option to the shopt builtin). Setting extdebug after the shell has started to execute a script, or referencing this variable when extdebug is not set, may result in inconsistent values.

BASH_ARGV0
When referenced, this variable expands to the name of the shell or shell script (identical to \$0; See Special Parameters, for the description of special parameter 0). Assignment to BASH_ARGV0 causes the value assigned to also be assigned to $0. If BASH_ARGV0 is unset, it loses its special properties, even if it is subsequently reset.

BASH_CMDS
An associative array variable whose members correspond to the internal hash table of commands as maintained by the hash builtin (see Bourne Shell Builtins). Elements added to this array appear in the hash table; however, unsetting array elements currently does not cause command names to be removed from the hash table. If BASH_CMDS is unset, it loses its special properties, even if it is subsequently reset.

BASH_COMMAND
The command currently being executed or about to be executed, unless the shell is executing a command as the result of a trap, in which case it is the command executing at the time of the trap. If BASH_COMMAND is unset, it loses its special properties, even if it is subsequently reset.

BASH_COMPAT
The value is used to set the shell’s compatibility level. See Shell Compatibility Mode, for a description of the various compatibility levels and their effects. The value may be a decimal number (e.g., 4.2) or an integer (e.g., 42) corresponding to the desired compatibility level. If BASH_COMPAT is unset or set to the empty string, the compatibility level is set to the default for the current version. If BASH_COMPAT is set to a value that is not one of the valid compatibility levels, the shell prints an error message and sets the compatibility level to the default for the current version. The valid values correspond to the compatibility levels described below (see Shell Compatibility Mode). For example, 4.2 and 42 are valid values that correspond to the compat42 shopt option and set the compatibility level to 42. The current version is also a valid value.

BASH_ENV
If this variable is set when Bash is invoked to execute a shell script, its value is expanded and used as the name of a startup file to read before executing the script. See Bash Startup Files.

BASH_EXECUTION_STRING
The command argument to the -c invocation option.

BASH_LINENO
An array variable whose members are the line numbers in source files where each corresponding member of FUNCNAME was invoked. \${BASH_LINENO\[\$i]} is the line number in the source file (\${BASH_SOURCE\[\$i+1]}) where ${FUNCNAME\[\$i]} was called (or \${BASH_LINENO\[\$i-1]} if referenced within another shell function). Use LINENO to obtain the current line number.

BASH_LOADABLES_PATH
A colon-separated list of directories in which the shell looks for dynamically loadable builtins specified by the enable command.

BASH_REMATCH
An array variable whose members are assigned by the ‘=~’ binary operator to the [[ conditional command (see Conditional Constructs). The element with index 0 is the portion of the string matching the entire regular expression. The element with index n is the portion of the string matching the nth parenthesized subexpression.

BASH_SOURCE
An array variable whose members are the source filenames where the corresponding shell function names in the FUNCNAME array variable are defined. The shell function \${FUNCNAME\[\$i]} is defined in the file \${BASH_SOURCE\[\$i]} and called from \${BASH_SOURCE\[\$i+1]}

BASH_SUBSHELL
Incremented by one within each subshell or subshell environment when the shell begins executing in that environment. The initial value is 0. If BASH_SUBSHELL is unset, it loses its special properties, even if it is subsequently reset.

BASH_VERSINFO
A readonly array variable (see Arrays) whose members hold version information for this instance of Bash. The values assigned to the array members are as follows:

BASH_VERSINFO[0]
The major version number (the release).

BASH_VERSINFO[1]
The minor version number (the version).

BASH_VERSINFO[2]
The patch level.

BASH_VERSINFO[3]
The build version.

BASH_VERSINFO[4]
The release status (e.g., beta1).

BASH_VERSINFO[5]
The value of MACHTYPE.

BASH_VERSION
The version number of the current instance of Bash.

BASH_XTRACEFD
If set to an integer corresponding to a valid file descriptor, Bash will write the trace output generated when ‘set -x’ is enabled to that file descriptor. This allows tracing output to be separated from diagnostic and error messages. The file descriptor is closed when BASH_XTRACEFD is unset or assigned a new value. Unsetting BASH_XTRACEFD or assigning it the empty string causes the trace output to be sent to the standard error. Note that setting BASH_XTRACEFD to 2 (the standard error file descriptor) and then unsetting it will result in the standard error being closed.

CHILD_MAX
Set the number of exited child status values for the shell to remember. Bash will not allow this value to be decreased below a POSIX-mandated minimum, and there is a maximum value (currently 8192) that this may not exceed. The minimum value is system-dependent.

COLUMNS
Used by the select command to determine the terminal width when printing selection lists. Automatically set if the checkwinsize option is enabled (see The Shopt Builtin), or in an interactive shell upon receipt of a SIGWINCH.

COMP_CWORD
An index into ${COMP_WORDS} of the word containing the current cursor position. This variable is available only in shell functions invoked by the programmable completion facilities (see Programmable Completion).

COMP_LINE
The current command line. This variable is available only in shell functions and external commands invoked by the programmable completion facilities (see Programmable Completion).

COMP_POINT
The index of the current cursor position relative to the beginning of the current command. If the current cursor position is at the end of the current command, the value of this variable is equal to ${#COMP_LINE}. This variable is available only in shell functions and external commands invoked by the programmable completion facilities (see Programmable Completion).

COMP_TYPE
Set to an integer value corresponding to the type of completion attempted that caused a completion function to be called: TAB, for normal completion, ‘?’, for listing completions after successive tabs, ‘!’, for listing alternatives on partial word completion, ‘@’, to list completions if the word is not unmodified, or ‘%’, for menu completion. This variable is available only in shell functions and external commands invoked by the programmable completion facilities (see Programmable Completion).

COMP_KEY
The key (or final key of a key sequence) used to invoke the current completion function.

COMP_WORDBREAKS
The set of characters that the Readline library treats as word separators when performing word completion. If COMP_WORDBREAKS is unset, it loses its special properties, even if it is subsequently reset.

COMP_WORDS
An array variable consisting of the individual words in the current command line. The line is split into words as Readline would split it, using COMP_WORDBREAKS as described above. This variable is available only in shell functions invoked by the programmable completion facilities (see Programmable Completion).

COMPREPLY
An array variable from which Bash reads the possible completions generated by a shell function invoked by the programmable completion facility (see Programmable Completion). Each array element contains one possible completion.

COPROC
An array variable created to hold the file descriptors for output from and input to an unnamed coprocess (see Coprocesses).

DIRSTACK
An array variable containing the current contents of the directory stack. Directories appear in the stack in the order they are displayed by the dirs builtin. Assigning to members of this array variable may be used to modify directories already in the stack, but the pushd and popd builtins must be used to add and remove directories. Assignment to this variable will not change the current directory. If DIRSTACK is unset, it loses its special properties, even if it is subsequently reset.

EMACS
If Bash finds this variable in the environment when the shell starts with value ‘t’, it assumes that the shell is running in an Emacs shell buffer and disables line editing.

ENV
Expanded and executed similarlty to BASH_ENV (see Bash Startup Files) when an interactive shell is invoked in POSIX Mode (see Bash POSIX Mode).

EPOCHREALTIME
Each time this parameter is referenced, it expands to the number of seconds since the Unix Epoch as a floating point value with micro-second granularity (see the documentation for the C library function time for the definition of Epoch). Assignments to EPOCHREALTIME are ignored. If EPOCHREALTIME is unset, it loses its special properties, even if it is subsequently reset.

EPOCHSECONDS
Each time this parameter is referenced, it expands to the number of seconds since the Unix Epoch (see the documentation for the C library function time for the definition of Epoch). Assignments to EPOCHSECONDS are ignored. If EPOCHSECONDS is unset, it loses its special properties, even if it is subsequently reset.

EUID
The numeric effective user id of the current user. This variable is readonly.

EXECIGNORE
A colon-separated list of shell patterns (see Pattern Matching) defining the list of filenames to be ignored by command search using PATH. Files whose full pathnames match one of these patterns are not considered executable files for the purposes of completion and command execution via PATH lookup. This does not affect the behavior of the [, test, and [[ commands. Full pathnames in the command hash table are not subject to EXECIGNORE. Use this variable to ignore shared library files that have the executable bit set, but are not executable files. The pattern matching honors the setting of the extglob shell option.

FCEDIT
The editor used as a default by the -e option to the fc builtin command.

FIGNORE
A colon-separated list of suffixes to ignore when performing filename completion. A filename whose suffix matches one of the entries in FIGNORE is excluded from the list of matched filenames. A sample value is ‘.o:~’

FUNCNAME
An array variable containing the names of all shell functions currently in the execution call stack. The element with index 0 is the name of any currently-executing shell function. The bottom-most element (the one with the highest index) is "main". This variable exists only when a shell function is executing. Assignments to FUNCNAME have no effect. If FUNCNAME is unset, it loses its special properties, even if it is subsequently reset.

This variable can be used with BASH_LINENO and BASH_SOURCE. Each element of FUNCNAME has corresponding elements in BASH_LINENO and BASH_SOURCE to describe the call stack. For instance, \${FUNCNAME\[\$i]} was called from the file \${BASH_SOURCE\[\$i+1]} at line number \${BASH_LINENO\[\$i]}. The caller builtin displays the current call stack using this information.

FUNCNEST
If set to a numeric value greater than 0, defines a maximum function nesting level. Function invocations that exceed this nesting level will cause the current command to abort.

GLOBIGNORE
A colon-separated list of patterns defining the set of file names to be ignored by filename expansion. If a file name matched by a filename expansion pattern also matches one of the patterns in GLOBIGNORE, it is removed from the list of matches. The pattern matching honors the setting of the extglob shell option.

GROUPS
An array variable containing the list of groups of which the current user is a member. Assignments to GROUPS have no effect. If GROUPS is unset, it loses its special properties, even if it is subsequently reset.

histchars
Up to three characters which control history expansion, quick substitution, and tokenization (see History Interaction). The first character is the history expansion character, that is, the character which signifies the start of a history expansion, normally ‘!’. The second character is the character which signifies ‘quick substitution’ when seen as the first character on a line, normally ‘^’. The optional third character is the character which indicates that the remainder of the line is a comment when found as the first character of a word, usually ‘#’. The history comment character causes history substitution to be skipped for the remaining words on the line. It does not necessarily cause the shell parser to treat the rest of the line as a comment.

HISTCMD
The history number, or index in the history list, of the current command. Assignments to HISTCMD are ignored. If HISTCMD is unset, it loses its special properties, even if it is subsequently reset.

HISTCONTROL
A colon-separated list of values controlling how commands are saved on the history list. If the list of values includes ‘ignorespace’, lines which begin with a space character are not saved in the history list. A value of ‘ignoredups’ causes lines which match the previous history entry to not be saved. A value of ‘ignoreboth’ is shorthand for ‘ignorespace’ and ‘ignoredups’. A value of ‘erasedups’ causes all previous lines matching the current line to be removed from the history list before that line is saved. Any value not in the above list is ignored. If HISTCONTROL is unset, or does not include a valid value, all lines read by the shell parser are saved on the history list, subject to the value of HISTIGNORE. The second and subsequent lines of a multi-line compound command are not tested, and are added to the history regardless of the value of HISTCONTROL.

HISTFILE
The name of the file to which the command history is saved. The default value is ~/.bash_history.

HISTFILESIZE
The maximum number of lines contained in the history file. When this variable is assigned a value, the history file is truncated, if necessary, to contain no more than that number of lines by removing the oldest entries. The history file is also truncated to this size after writing it when a shell exits. If the value is 0, the history file is truncated to zero size. Non-numeric values and numeric values less than zero inhibit truncation. The shell sets the default value to the value of HISTSIZE after reading any startup files.

HISTIGNORE
A colon-separated list of patterns used to decide which command lines should be saved on the history list. Each pattern is anchored at the beginning of the line and must match the complete line (no implicit ‘*’ is appended). Each pattern is tested against the line after the checks specified by HISTCONTROL are applied. In addition to the normal shell pattern matching characters, ‘&’ matches the previous history line. ‘&’ may be escaped using a backslash; the backslash is removed before attempting a match. The second and subsequent lines of a multi-line compound command are not tested, and are added to the history regardless of the value of HISTIGNORE. The pattern matching honors the setting of the extglob shell option.

HISTIGNORE subsumes the function of HISTCONTROL. A pattern of ‘&’ is identical to ignoredups, and a pattern of ‘[ ]*’ is identical to ignorespace. Combining these two patterns, separating them with a colon, provides the functionality of ignoreboth.

HISTSIZE
The maximum number of commands to remember on the history list. If the value is 0, commands are not saved in the history list. Numeric values less than zero result in every command being saved on the history list (there is no limit). The shell sets the default value to 500 after reading any startup files.

HISTTIMEFORMAT
If this variable is set and not null, its value is used as a format string for strftime to print the time stamp associated with each history entry displayed by the history builtin. If this variable is set, time stamps are written to the history file so they may be preserved across shell sessions. This uses the history comment character to distinguish timestamps from other history lines.

HOSTFILE
Contains the name of a file in the same format as /etc/hosts that should be read when the shell needs to complete a hostname. The list of possible hostname completions may be changed while the shell is running; the next time hostname completion is attempted after the value is changed, Bash adds the contents of the new file to the existing list. If HOSTFILE is set, but has no value, or does not name a readable file, Bash attempts to read /etc/hosts to obtain the list of possible hostname completions. When HOSTFILE is unset, the hostname list is cleared.

HOSTNAME
The name of the current host.

HOSTTYPE
A string describing the machine Bash is running on.

IGNOREEOF
Controls the action of the shell on receipt of an EOF character as the sole input. If set, the value denotes the number of consecutive EOF characters that can be read as the first character on an input line before the shell will exit. If the variable exists but does not have a numeric value, or has no value, then the default is 10. If the variable does not exist, then EOF signifies the end of input to the shell. This is only in effect for interactive shells.

INPUTRC
The name of the Readline initialization file, overriding the default of ~/.inputrc.

INSIDE_EMACS
If Bash finds this variable in the environment when the shell starts, it assumes that the shell is running in an Emacs shell buffer and may disable line editing depending on the value of TERM.

LANG
Used to determine the locale category for any category not specifically selected with a variable starting with LC_.

LC_ALL
This variable overrides the value of LANG and any other LC_ variable specifying a locale category.

LC_COLLATE
This variable determines the collation order used when sorting the results of filename expansion, and determines the behavior of range expressions, equivalence classes, and collating sequences within filename expansion and pattern matching (see Filename Expansion).

LC_CTYPE
This variable determines the interpretation of characters and the behavior of character classes within filename expansion and pattern matching (see Filename Expansion).

LC_MESSAGES
This variable determines the locale used to translate double-quoted strings preceded by a ‘$’ (see Locale Translation).

LC_NUMERIC
This variable determines the locale category used for number formatting.

LC_TIME
This variable determines the locale category used for data and time formatting.

LINENO
The line number in the script or shell function currently executing. If LINENO is unset, it loses its special properties, even if it is subsequently reset.

LINES
Used by the select command to determine the column length for printing selection lists. Automatically set if the checkwinsize option is enabled (see The Shopt Builtin), or in an interactive shell upon receipt of a SIGWINCH.

MACHTYPE
A string that fully describes the system type on which Bash is executing, in the standard GNU cpu-company-system format.

MAILCHECK
How often (in seconds) that the shell should check for mail in the files specified in the MAILPATH or MAIL variables. The default is 60 seconds. When it is time to check for mail, the shell does so before displaying the primary prompt. If this variable is unset, or set to a value that is not a number greater than or equal to zero, the shell disables mail checking.

MAPFILE
An array variable created to hold the text read by the mapfile builtin when no variable name is supplied.

OLDPWD
The previous working directory as set by the cd builtin.

OPTERR
If set to the value 1, Bash displays error messages generated by the getopts builtin command.

OSTYPE
A string describing the operating system Bash is running on.

PIPESTATUS
An array variable (see Arrays) containing a list of exit status values from the processes in the most-recently-executed foreground pipeline (which may contain only a single command).

POSIXLY_CORRECT
If this variable is in the environment when Bash starts, the shell enters POSIX mode (see Bash POSIX Mode) before reading the startup files, as if the --posix invocation option had been supplied. If it is set while the shell is running, Bash enables POSIX mode, as if the command

set -o posix
had been executed. When the shell enters POSIX mode, it sets this variable if it was not already set.

PPID
The process ID of the shell’s parent process. This variable is readonly.

PROMPT_COMMAND
If this variable is set, and is an array, the value of each set element is interpreted as a command to execute before printing the primary prompt ($PS1). If this is set but not an array variable, its value is used as a command to execute instead.

PROMPT_DIRTRIM
If set to a number greater than zero, the value is used as the number of trailing directory components to retain when expanding the \w and \W prompt string escapes (see Controlling the Prompt). Characters removed are replaced with an ellipsis.

PS0
The value of this parameter is expanded like PS1 and displayed by interactive shells after reading a command and before the command is executed.

PS3
The value of this variable is used as the prompt for the select command. If this variable is not set, the select command prompts with ‘#? ’

PS4
The value of this parameter is expanded like PS1 and the expanded value is the prompt printed before the command line is echoed when the -x option is set (see The Set Builtin). The first character of the expanded value is replicated multiple times, as necessary, to indicate multiple levels of indirection. The default is ‘+ ’.

PWD
The current working directory as set by the cd builtin.

RANDOM
Each time this parameter is referenced, it expands to a random integer between 0 and 32767. Assigning a value to this variable seeds the random number generator. If RANDOM is unset, it loses its special properties, even if it is subsequently reset.

READLINE_LINE
The contents of the Readline line buffer, for use with ‘bind -x’ (see Bash Builtins).

READLINE_MARK
The position of the mark (saved insertion point) in the Readline line buffer, for use with ‘bind -x’ (see Bash Builtins). The characters between the insertion point and the mark are often called the region.

READLINE_POINT
The position of the insertion point in the Readline line buffer, for use with ‘bind -x’ (see Bash Builtins).

REPLY
The default variable for the read builtin.

SECONDS
This variable expands to the number of seconds since the shell was started. Assignment to this variable resets the count to the value assigned, and the expanded value becomes the value assigned plus the number of seconds since the assignment. The number of seconds at shell invocation and the current time is always determined by querying the system clock. If SECONDS is unset, it loses its special properties, even if it is subsequently reset.

SHELL
This environment variable expands to the full pathname to the shell. If it is not set when the shell starts, Bash assigns to it the full pathname of the current user’s login shell.

SHELLOPTS
A colon-separated list of enabled shell options. Each word in the list is a valid argument for the -o option to the set builtin command (see The Set Builtin). The options appearing in SHELLOPTS are those reported as ‘on’ by ‘set -o’. If this variable is in the environment when Bash starts up, each shell option in the list will be enabled before reading any startup files. This variable is readonly.

SHLVL
Incremented by one each time a new instance of Bash is started. This is intended to be a count of how deeply your Bash shells are nested.

SRANDOM
This variable expands to a 32-bit pseudo-random number each time it is referenced. The random number generator is not linear on systems that support /dev/urandom or arc4random, so each returned number has no relationship to the numbers preceding it. The random number generator cannot be seeded, so assignments to this variable have no effect. If SRANDOM is unset, it loses its special properties, even if it is subsequently reset.

TIMEFORMAT
The value of this parameter is used as a format string specifying how the timing information for pipelines prefixed with the time reserved word should be displayed. The ‘%’ character introduces an escape sequence that is expanded to a time value or other information. The escape sequences and their meanings are as follows; the braces denote optional portions.

%%
A literal ‘%’.

%[p][l]R
The elapsed time in seconds.

%[p][l]U
The number of CPU seconds spent in user mode.

%[p][l]S
The number of CPU seconds spent in system mode.

%P
The CPU percentage, computed as (%U + %S) / %R.

The optional p is a digit specifying the precision, the number of fractional digits after a decimal point. A value of 0 causes no decimal point or fraction to be output. At most three places after the decimal point may be specified; values of p greater than 3 are changed to 3. If p is not specified, the value 3 is used.

The optional l specifies a longer format, including minutes, of the form MMmSS.FFs. The value of p determines whether or not the fraction is included.

If this variable is not set, Bash acts as if it had the value

$'\nreal\t%3lR\nuser\t%3lU\nsys\t%3lS'
If the value is null, no timing information is displayed. A trailing newline is added when the format string is displayed.

TMOUT
If set to a value greater than zero, TMOUT is treated as the default timeout for the read builtin (see Bash Builtins). The select command (see Conditional Constructs) terminates if input does not arrive after TMOUT seconds when input is coming from a terminal.

In an interactive shell, the value is interpreted as the number of seconds to wait for a line of input after issuing the primary prompt. Bash terminates after waiting for that number of seconds if a complete line of input does not arrive.

TMPDIR
If set, Bash uses its value as the name of a directory in which Bash creates temporary files for the shell’s use.

UID
The numeric real user id of the current user. This variable is readonly.

## 9 Using History Interactively

This chapter describes how to use the GNU History Library interactively, from a user’s standpoint. It should be considered a user’s guide. For information on using the GNU History Library in other programs, see the GNU Readline Library Manual.

### 9.1 Bash History Facilities
When the -o history option to the set builtin is enabled (see The Set Builtin), the shell provides access to the command history, the list of commands previously typed. The value of the HISTSIZE shell variable is used as the number of commands to save in a history list. The text of the last $HISTSIZE commands (default 500) is saved. The shell stores each command in the history list prior to parameter and variable expansion but after history expansion is performed, subject to the values of the shell variables HISTIGNORE and HISTCONTROL.

When the shell starts up, the history is initialized from the file named by the HISTFILE variable (default ~/.bash_history). The file named by the value of HISTFILE is truncated, if necessary, to contain no more than the number of lines specified by the value of the HISTFILESIZE variable. When a shell with history enabled exits, the last $HISTSIZE lines are copied from the history list to the file named by $HISTFILE. If the histappend shell option is set (see Bash Builtins), the lines are appended to the history file, otherwise the history file is overwritten. If HISTFILE is unset, or if the history file is unwritable, the history is not saved. After saving the history, the history file is truncated to contain no more than $HISTFILESIZE lines. If HISTFILESIZE is unset, or set to null, a non-numeric value, or a numeric value less than zero, the history file is not truncated.

If the HISTTIMEFORMAT is set, the time stamp information associated with each history entry is written to the history file, marked with the history comment character. When the history file is read, lines beginning with the history comment character followed immediately by a digit are interpreted as timestamps for the following history entry.

The builtin command fc may be used to list or edit and re-execute a portion of the history list. The history builtin may be used to display or modify the history list and manipulate the history file. When using command-line editing, search commands are available in each editing mode that provide access to the history list (see Commands For History).

The shell allows control over which commands are saved on the history list. The HISTCONTROL and HISTIGNORE variables may be set to cause the shell to save only a subset of the commands entered. The cmdhist shell option, if enabled, causes the shell to attempt to save each line of a multi-line command in the same history entry, adding semicolons where necessary to preserve syntactic correctness. The lithist shell option causes the shell to save the command with embedded newlines instead of semicolons. The shopt builtin is used to set these options. See The Shopt Builtin, for a description of shopt.

