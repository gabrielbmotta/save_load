# save_load

Quick library to save/load either strings or integers in plaintext. 

## Syntax

Each entry consists of a key and a value. Entries have the following form:

```
KEY_NAME=<VALUE>
```

where the value syntax depends on the type. There should be no whitespace surrounding the equal sign(`=`).

### Keys

Valid keys should be made up of non-whitespace characters.

### Values

#### Integers

To denote integer values, simply write out the value after the equal sign.

```
MY_INT_KEY=33
```

#### Strings

To denote a string, enclose the string in three angle braces `<<<My string.>>>`

```
MY_STRING_KEY=<<<This is a string>>>
```

Strings can also span multiple lines. This works the same way, just enclose the string in three angle brances.

```
MY_ML_STRING_KEY=<<<This is
a multiline
string>>>
```

### Comments

Lines that start with `###` will be ignored.

```
###THING=4
THING=5
```
