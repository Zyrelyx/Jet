# VSP Assignment

## Introduction

The goal of this exercise is to apply the material learned in the ESP lecture within the context of a larger practical exercise in a group. This involves learning and applying skills related to handling strings, dynamic memory, structs, lists, and so on. Additionally, the exercise focuses on dealing with directed graphs.

## Learning Goals

- Heap and Memory Management
- File I/O
- Structs

## Specification and Grading

The program must be written in C. 

As this is the only task in this course, it is assessed with 100 % of the points in VSP. You can achieve 100 points for this assignment. Please note that the test cases alone do not determine your final grade. You may receive point deductions for various violations (see [Assessment of Assignments - Deductions](https://www.notion.so/9d0a6b7d9876422ba8f4745679db45b9?pvs=21)) and at the assignment interview.

## Submission

- Deliverables: all files (.h and .c) needed to run your program, the main function must be in a file called `assignment.c`
- Push to your team repository
- **Deadline: 15.02.2024 23:59 (GMT+1)**

## General Notes

The notes given in this section are important for the whole assignment description.

- `\n` shouldn't be printed as separate characters, instead it represents the newline character.
- Words in sharp brackets (like `<NAME>`) should be replaced by calculated or given data. They are *not* part of the output itself! For a better understanding you can look at the example outputs at the end of this document.
- `vsp>`  (command prompt, always printed with a trailing space) in the output signifies that the program should wait for a user input at this point. Execution should only continue after the user has ended their input with `ENTER`
- All additional whitespaces (leading, trailing, or additional whitespaces between command and parameters or between two parameters) in the input should be ignored. Attention: Parameters themselves may also contain whitespaces (e.g. in the name of a person)!
- The user input is **case-sensitive**. This means that `quit` is a valid command, but `Quit` and `QUIT` would be invalid inputs.

## Assignment Description

Professor Arno Science is engaged in genealogy (Ahnenforschung) and is asking for a program that significantly simplifies his work. He wants to be able to input family relationships easily, analyze them, and also visually represent them. For graphical representation, he specifies the use of the simple and practical description language DOT, commonly used for graph visualization. A file conforming to this language can be easily rendered into a PNG file, visually displaying the family tree of a specific individual or an entire lineage (see section Program Sequence > DOT File).

Professor Arno Science asks his programming teams to familiarize themselves with directed graph data structures. Nevertheless, he provides a brief introduction to graph theory: *"Please think about your family tree. You are the root, positioned at the top. Below you are two nodes, which represent your parents, and then each of them has two more nodes connected to them, representing your grandparents.”*

Creating a family tree involves specifying (grand-)parental relationships. This constitutes the information input for the program.

The program then should be able to check, based on a given input file or entered data, whether a family relationship exists between two specific individuals or not. Professor Science emphasizes, *"This information is essential for inheritances, historical events, or even fundamental for medicine.”*

When adding new nodes, it's important to note that there might be certain internal nodes whose names are unknown. While every person must theoretically have parents, adding a known grandparent, for example, doesn't necessarily require knowing the names of the parents. In such cases, the Professor simply asks his teams to use a placeholder as the unknown parent node, as he has done in his previous work.

Just like in other research areas, in genealogy, it's possible to make mistakes and create incorrect family relationships based on inaccurate information. Consequently, there might be a need to delete or rename a previously added node. 

Professor Arno Science also advises keeping the graph as small as possible, as it could *"end up going to infinity”,* so a [pruning algorithm](https://www.geeksforgeeks.org/trim-given-binary-tree-for-any-subtree-containing-only-0s/) should be implemented.

Thus, the Professor has shared the general requirements. The details can be found later on this page.

*"Wishing you success and lots of enjoyment!"* - Professor Science extends his best wishes to his programming teams.

## Program Sequence

<details>
<summary><h4>Person</h4></summary>

In the program, each node in the graph represents a person. A person has two characteristics: 

1. A name, which is a string.
2. An ID, which is an integer.  

The ID is unique over all persons and is written after the name in square brackets in the output. 

Examples:

`Ned Stark [2]` 

`Catelyn Tully [3]`

A person can have up to two parents, which we refer to as `parent1` and `parent2`.

***
</details>



<details>
<summary><h4>DOT Files</h4></summary>

DOT files are used as inputs and outputs by the program to represent family trees.

For a general description, please refer to the informative [Wikipedia page](https://de.wikipedia.org/wiki/DOT_(GraphViz)) about the DOT format by GraphViz. For this program, only directed graphs are relevant.

The following text describes the specific file format that will be used by the program. All input files that will be tested contain family trees in the following format. When your program creates new DOT files containing family trees, they should also follow this format.

Each file contains exactly one "digraph" block, which is always named "FamilyTree."

After the header ("digraph FamilyTree"), there follows a block enclosed in curly braces, containing zero to infinite relationships between persons line by line, each line having two leading spaces. The block braces are placed on line 2 and on the last line, standing alone and without leading spaces. 

Each relationship line is terminated by a semicolon. Arrows (`->`) indicate the direction of the relationship between the persons (the child is on the left side of the arrow, the parent on the right). Only one relationship is specified per line. All persons (in the format specified above) are contained within quotation marks.

The relationships are sorted by the ID of the child. The relationship to parent1 should always be listed first, followed by the relationship to parent2. If only one parent exists, only this relationship is listed. If there are no parents at all, the person is a node with no outgoing edges. This means that no relationship that contains this person as a child will be listed in the DOT file.

As mentioned earlier, it can happen that there are persons with unknown names in the family tree. These are represented in the file by question marks ("? [\<ID>]").

It is possible that a DOT file contains a list of relationships that results in multiple family trees that are not connected to each other.

This is an example of a DOT file containing a valid family tree:


```txt
digraph FamilyTree\n
{\n
  "Benjen Stark [3]" -> "Rickard Stark [1]";\n
  "Benjen Stark [3]" -> "Lyarra Stark [2]";\n
  "Eddard Stark [4]" -> "Rickard Stark [1]";\n
  "Eddard Stark [4]" -> "Lyarra Stark [2]";\n
  "Jon Snow [6]" -> "Eddard Stark [4]";\n
  "Jon Snow [6]" -> "? [10]";\n
  "Robb Stark [7]" -> "Catelyn Tully [5]";\n
  "Robb Stark [7]" -> "Eddard Stark [4]";\n
  "Sansa Stark [8]" -> "Eddard Stark [4]";\n
  "Sansa Stark [8]" -> "Catelyn Tully [5]";\n
  "Arya Stark [9]" -> "Eddard Stark [4]";\n
  "Arya Stark [9]" -> "Catelyn Tully [5]";\n
}\n
```
A DOT file can be converted into a PNG image for easier checking :

<details>
<summary><h5>Linux</h5></summary>

To convert a file into a PNG image, you first need to install the necessary software.

`sudo apt-get install graphviz`

Once the installation is complete, you can convert the DOT file:

`dot -Tpng example_fam-tree.dot > example_fam-tree.png`
</details>
<details>
<summary><h5>Web</h5></summary>

Go to https://dreampuf.github.io/GraphvizOnline/ and copy the contents of the DOT file into the box on the left. Change the format to png_image_element in the dropdown list on the right. The image of the converted graph is displayed and can also be downloaded.
</details>

This image was created using the above DOT file: ![Example Family Tree](https://dreampuf.github.io/GraphvizOnline/#digraph%20FamilyTree%0A%7B%0A%20%20%22Benjen%20Stark%20%5B3%5D%22%20-%3E%20%22Rickard%20Stark%20%5B1%5D%22%3B%0A%20%20%22Benjen%20Stark%20%5B3%5D%22%20-%3E%20%22Lyarra%20Stark%20%5B2%5D%22%3B%0A%20%20%22Eddard%20Stark%20%5B4%5D%22%20-%3E%20%22Rickard%20Stark%20%5B1%5D%22%3B%0A%20%20%22Eddard%20Stark%20%5B4%5D%22%20-%3E%20%22Lyarra%20Stark%20%5B2%5D%22%3B%0A%20%20%22Robb%20Stark%20%5B7%5D%22%20-%3E%20%22Catelyn%20Tully%20%5B5%5D%22%3B%0A%20%20%22Robb%20Stark%20%5B7%5D%22%20-%3E%20%22Eddard%20Stark%20%5B4%5D%22%3B%0A%20%20%22Jon%20Snow%20%5B6%5D%22%20-%3E%20%22Eddard%20Stark%20%5B4%5D%22%3B%0A%20%20%22Jon%20Snow%20%5B6%5D%22%20-%3E%20%22%3F%20%5B10%5D%22%3B%0A%20%20%22Sansa%20Stark%20%5B8%5D%22%20-%3E%20%22Eddard%20Stark%20%5B4%5D%22%3B%0A%20%20%22Sansa%20Stark%20%5B8%5D%22%20-%3E%20%22Catelyn%20Tully%20%5B5%5D%22%3B%0A%20%20%22Arya%20Stark%20%5B9%5D%22%20-%3E%20%22Eddard%20Stark%20%5B4%5D%22%3B%0A%20%20%22Arya%20Stark%20%5B9%5D%22%20-%3E%20%22Catelyn%20Tully%20%5B5%5D%22%3B%0A%7D%0A)

***
</details>


<details>
<summary><h4>Starting the Program</h2></summary>

<details>
<summary><h5>General</h5></summary>

The program is called with zero or one command line parameter(s).
To start the program with an empty family tree, the following command is used:

`./assignment`

Alternatively, the program can be started with a single command line parameter, which specifies the path to a DOT input file that contains an existing family tree.

`./assignment example_fam-tree.dot`

If the program is called 

- with the wrong number of parameters
- with an input file that cannot be opened for reading

the corresponding error message should be printed and the program should terminate with the correct return value (see [Return Values and Error Messages](#return-values-and-error-messages)).
***
</details>


<details>
<summary><h5>Input File</h5></summary>

If the program was called with a file that can be opened, you can assume that this is a valid DOT file that contains a (possibly empty) family tree graph. The input file should be checked for the following conditions:

- The name of the digraph must be `FamilyTree`
- Each person can have at most two parents

If one of these conditions does not apply, the corresponding error message should be printed and the program should terminate with the correct return value (see [Return Values and Error Messages](#return-values-and-error-messages)).

For a detailed description of the files, see the section DOT Files.

After checking the validity of the input file, the internal representation of the family tree contained in it should be created.

If a person only has one parent in the input file, this parent should always be set as `parent1`.
If a person has two parents in the input file, the parent listed first should be set as `parent1` and second-listed parent should be set as `parent2`.
***
</details>


<details>
<summary><h5>Welcome Message</h5></summary>

Next the following welcome message is printed:

```
Welcome to the VSP Family Tree!\n
\n
```
***
</details>

</details>


<details>
<summary><h4>Running the Program</h4></summary>

<details>
<summary><h5>Command Prompt and User Input Handling</h5></summary>

The command prompt (note the trailing space) should be displayed in an endless loop while waiting for user input.

```txt
vsp> 
```

If the user only presses `ENTER` and makes no input, the command prompt should be printed again and the program should wait for another user input.

If the user enters an invalid command, i.e., a command that does not exist, it should be ignored, the command prompt should be printed again and the program should wait for another user input.

If the user enters a command that exists, but with the wrong number of parameters, the corresponding error message (see [Return Values and Error Messages](#return-values-and-error-messages)) should be printed.  Then a `\n` followed again by the command prompt should be printed, and the program should wait for another user input.

If the user enters a command that exists with a correct number of parameters, it should be handled as described in Running the Program > Commands. Then a `\n` followed again by the command prompt should be printed, and the program should wait for another user input (see [Examples](#examples)).
***
</details>

<details>
<summary><h5>Commands</h5></summary>

These are the valid commands that should be recognized and handled by the program:

<details>
<summary><h5>Command: help</h5></summary>

- `help`

The  `help` command prints the following help text:

```
Available commands:\n
- help: Display this help message.\n
- add <person name>\n
  Add a new person to the program\n
- list\n
  Print all individuals that have been added (or initially imported)\n
- connect <id> <relation> <id>\n
  Connect a person to another person and specify their relationship\n
- rename <id> <new name>\n
  Rename an existing person\n
- delete <id>\n
  Remove an existing person from the family tree\n
- draw-all <filename>\n
  Write all relationships to the terminal or a DOT file. <filename> is optional\n
- draw <id> <filename>\n
  Write all ancestors of a person to the terminal or a DOT file. <filename> is optional\n
- relationship <id1> <id2>\n
  Find out whether a family relationship exists between two indivduals\n
- prune\n
  Remove unkown leaf nodes from tree(s)\n
- quit\n
  End the program\n
\n
```

##### Error Handling

The following errors must be handled (see [Return Values and Error Messages](#return-values-and-error-messages)): 
- The command was called with too many or too few parameters

***
</details>

<details>
<summary><h5>Command: add</h5></summary>

- `add <PERSON-NAME>`

The `add` command adds a new person to the program. The parameter must specify the name of the newly created person. The name may include whitespaces. 

Since persons in the program are identified by their ID, the program needs to make sure that all IDs are unique. If there were any persons added via an input file, the IDs for newly created persons start at one higher than the highest ID to be found in the input file. Otherwise the IDs for newly created persons start at `1`. The next ID is always the last assigned ID plus one, no matter if all persons with lower IDs (still) exist.

The new person should be assigned the next highest unique ID.

It is possible to add persons with the same name, so it's up to the user to choose distinct names if they want to. Inside the program, each person is uniquely identified by their ID. 

After an `add` command was completed successfully, the text `Successfully created <NAME> [<ID>]!\n` should be printed. \<NAME> refers to the name of the person and \<ID> to the uniquely assigned ID. 

Example: 

```
vsp> add Jon Snow
Successfully created Jon Snow [22]!

vsp>
```

##### Error Handling

The following errors must be handled (see [Return Values and Error Messages](#return-values-and-error-messages)):

- The command was called with too many or too few parameters

***
</details>

<details>
<summary><h5>Command: list</h5></summary>

- `list`

This command should print all individuals that have been added (or initially imported) line by line in the person format, sorted by ID. In front of the name `- ` should be printed. 

This command provides a good overview of all individuals and their IDs. If a person is currently not connected to any other person (either as a parent or a child), an asterisk symbol should be printed after the ID. At the end of the list, the information `Persons with an asterisk (*) are not connected to any other person.\n` should be printed. 

If there are no persons nothing should be printed. Unknown persons (the name is only a question mark ”?”) should also be listed. 

Here is a small example of a valid `list` command:

```
vsp> list
- Eddard Stark [2]
- Catelyn Tully [3]
- Robb Stark [7]
- Sansa Stark [8]
- Tyrion Lannister [23]*
Persons with an asterisk (*) are not connected to any other person.

vsp> 
```

Directly after starting the program (without an input file), this command would provide the following output:

```
vsp> list

vsp> 
```

##### Error Handling

The following errors must be handled (see [Return Values and Error Messages](#return-values-and-error-messages)):

- The command was called with too many or too few parameters

***
</details>

<details>
<summary><h5>Command: connect</h5></summary>

- `connect <ID> <RELATION> <ID>`

The connect command connects an existing person to another existing person and specifies their relationship. Besides the ID of both persons, a relation parameter must be provided. The relationship is always viewed from the perspective of the first-mentioned person.

The following relationships are valid:

- `parent1`\
Example: `connect 4 parent1 8` adds a relation where the person with the ID `4` is parent1 of the person with the ID `8`.
- `parent2`\
Example: `connect 5 parent2 8` adds a relation where the person with the ID `5` is parent2 of the person with the ID `8`.
- `<parent1/parent2>:<gp1/gp2>` \
  `gp` stands for grandparent. This adds a relation between a grandchild and a grandparent directly. 
  A person can have up to four grandparents.  `gp1` means that it is parent1 of a parent, whereas `gp2` means it is parent2 of a parent.
  
  The parent which is between the grandchild and the grandparent, so on which side the grandparent should be added, is specified by writing `parent1` or `parent2`.  If the parent in this position does not yet exist, an unknown placeholder person named “?” should be added. This placeholder person should be assigned the next highest unique ID. To inform the user about the newly created unknown person, the message `Created unknown <parent1/parent2> [<ID>]!\n`  should be printed.

  ##### Example 1:
  `connect 1 parent1:gp1 8` adds a relation where the person with the ID `1` is the grandparent of the person with the ID `8`. The person with the ID `1` is parent1 of parent1 of the person with the ID `8`.  Parent1 of the person with the ID `8` might be an existing person or might be an unknown placeholder person.
      
  ##### Example 2: 
  `connect 2 parent1:gp2 8` adds a relation where the person with the ID `2` is the grandparent of the person with the ID `8`. The person with the ID `2` is parent2 of parent1 of the person with the ID `8`.  Parent1 of the person with the ID `8` might be an existing person or might be an unknown placeholder person.
      

  After a `connect` command was completed successfully, the message `Successfully connected <NAME> [<ID>] as <RELATION> of <NAME> [<ID>]!\n` should be printed.

##### Example

```
vsp> connect 4 parent1 8
Successfully connected Eddard Stark [4] as parent1 of Sansa Stark [8]!

vsp> connect 2 parent1:gp1 8
Successfully connected Lyarra Stark [2] as parent1:gp1 of Sansa Stark [8]!

vsp>
```

##### Error Handling

The following errors must be handled (see [Return Values and Error Messages](#return-values-and-error-messages)):

- The command was called with too many or too few parameters

- The given ID(s) do(es) not exist \
  The given ID is not an integer or could not be found in the program. \
  If both IDs do not exist, the error should be printed for the first ID.

Example:

```
vsp> connect 2 parent1 22
Successfully connected Eddard Stark [2] as parent1 of Jon Snow [22]!

vsp> connect 3333 parent1 2
Error: ID 3333 does not exist. Use 'list' to find all available persons.

vsp> 
```

- The given relation parameter does not exist

- Relationship already set \
  If the relationship is already set (with a known or unknown person), it should not be possible to set it again. In the case of adding a relationship to a grandparent, only the grandparent node should be checked. 

Examples:

```
vsp> connect 4 parent1 8
Successfully connected Eddard Stark [4] as parent1 of Sansa Stark [8]!

vsp> connect 5 parent1 8
Error: Relationship already set.

vsp> connect 5 parent2 8
Successfully connected Catelyn Tully [5] as parent2 of Sansa Stark [8]!

vsp>
```

```
vsp> connect 2 parent1:gp1 8
Successfully connected Lyarra Stark [2] as parent1:gp1 of Sansa Stark [8]!

vsp> connect 1 parent1:gp1 8
Error: Relationship already set.

vsp> connect 1 parent1:gp2 8
Successfully connected Rickard Stark [1] as parent1:gp2 of Sansa Stark [8]!

vsp> 
```

***
</details>


<details>
<summary><h5>Command: rename</h5></summary>

- `rename <ID> <NEW-NAME>`

The `rename` command renames an existing person. The \<ID> parameter must specify the ID of the person to be renamed, the \<NEW-NAME> parameter defines the new name of the person. The new name may contain whitespaces.

If successful, the text `Renaming <OLD-NAME> [<ID>] to <NEW-NAME> [<ID>] was successful!\n` should be printed. 

Example:

```
vsp> rename 25 The Dragon Queen
Renaming Daenerys Targaryen [25] to The Dragon Queen [25] was successful!

vsp> 
```

##### Error Handling

The following errors must be handled (see [Return Values and Error Messages](#return-values-and-error-messages)): 

- The command was called with too many or too few parameters
- The given ID(s) do(es) not exist\
  The given ID is not an integer or could not be found in the program.

***
</details>

<details>
<summary><h5>Command: delete</h5></summary>

- `delete <ID>`

The `delete` command removes a person from the family tree. The \<ID> parameter must specify the ID of the person to be deleted. When deleting a person, **only the name of the person is set to a question mark “?”**. The ID stays the same and the person node stays in the family tree as a placeholder. Subsequent `list` commands should also still list this person, but with the unknown name.

If successful, the text `Deleting <NAME> [<ID>] was successful!\n` should be printed. 

Example:

```
vsp> delete 22
Deleting Jon Snow [22] was successful!

vsp> delete 77777
Error: ID 77777 does not exist. Use 'list' to find all available persons.

vsp> 
```

##### Error Handling

The following errors must be handled (see [Return Values and Error Messages](#return-values-and-error-messages)): 

- The command was called with too many or too few parameters
- The given ID(s) do(es) not exist\
  The given ID is not an integer or could not be found in the program.

***
</details>


<details>
<summary><h5>Command: draw-all</h5></summary>

- `draw-all <FILE-NAME>`

The `draw-all` command writes all relationships to the terminal or to a DOT file (for the correct format see section DOT Files). The parameter `<FILE-NAME>` is **optional** and defines the name for the output file. 

If the parameter is provided, a digraph FamilyTree with all relationships should be written to this output file (there should be no spaces within the file name). The program should automatically add the extension `.dot`. If there are currently no relationships, an empty digraph FamilyTree should be written to the file. If successful, the message `Creating DOT-file was successful!\n` should be printed.

If the parameter `<FILE-NAME>` is not provided, the relationships (only the content inside the curly brackets `{` and `}` without the `"` and `;`, see example below) should be written to the terminal instead. Semicolons and quotation marks should not be printed, but the output should start with 2 whitespaces in each line. If there are currently no relationships, nothing should be printed.

##### Error Handling

The following errors must be handled  (see [Return Values and Error Messages](#return-values-and-error-messages)):

- The command was called with too many or too few parameters
- The program cannot write the desired output file

Examples:

```
vsp> draw-all fam-tree
Creating DOT-file was successful!

vsp> draw-all error-file
Error: Could not write file.

vsp> draw-all
  Benjen Stark [3] -> Rickard Stark [1]
  Benjen Stark [3] -> Lyarra Stark [2]
  Eddard Stark [4] -> Rickard Stark [1]
  Eddard Stark [4] -> Lyarra Stark [2]
  Jon Snow [6] -> Eddard Stark [4]
  Jon Snow [6] -> ? [10]
  Robb Stark [7] -> Catelyn Tully [5]
  Robb Stark [7] -> Eddard Stark [4]
  Sansa Stark [8] -> Eddard Stark [4]
  Sansa Stark [8] -> Catelyn Tully [5]
  Arya Stark [9] -> Eddard Stark [4]
  Arya Stark [9] -> Catelyn Tully [5]

vsp> 
```
***
</details>


<details>
<summary><h5>Command: draw</h5></summary>

- `draw <ID> <FILE-NAME>`

The `draw` command differs from the above in that it specifies the \<ID> of a person for whom the family tree should be written to file or to the terminal. This means that the specified person represents the root, and only parent relationships are written until all leaves are reached. If the specified person is already a leaf node, nothing should be printed. For the correct format see section DOT Files. 

The parameter `<FILE-NAME>` is **optional** (similar to draw-all) and defines the name for the output file. 

If the parameter is provided, a digraph FamilyTree with all relevant relationships should be written to this output file (there should be no spaces within the file name). The program should automatically add the extension `.dot`. If the specified person has no parents, an empty digraph FamilyTree should be written to the file. If successful, the message `Creating DOT-file was successful!\n` should be printed. 

If the parameter `<FILE-NAME>` is not provided, the relevant relationships (only the content inside the curly brackets `{` and `}` without the `"` and `;`) should be written to the terminal instead. If the specified person has no parents, nothing should be printed.

##### Error Handling

The following errors must be handled (see [Return Values and Error Messages](#return-values-and-error-messages)) :

- The command was called with too many or too few parameters
- The given ID(s) do(es) not exist\
  The given ID is not an integer or could not be found in the program. \
- The program cannot write the desired output file

***
</details>

<details>
<summary><h5>Command: relationship</h5></summary>

- `relationship <ID1> <ID2>`

As the name of the `relationship` command already suggests, the goal here is to find out whether a family relationship exists between the specified individuals or not. If one of the following family relationships is present, the type of relation must also be printed:

- sibling \
  (The individuals have the same parents. If either parent is different or not set, the individuals should not be identified as siblings. If the parents are the same but swapped in the `parent1` and `parent2` relationships, the individuals should be identified as siblings.)
- parent
- grandparent
- child
- grandchild

`<ID1>`: The ID of the first person

`<ID2>`:  The ID of the second person

Two people are related if they either share an ancestor, or one is an ancestor of the other.

If there is no relationship, `There is no relationship between <NAME1> [<ID1>] and <NAME2> [<ID2>].\n` should be printed.

If the two specified individuals are related, then, in any case, `<NAME1> [<ID1>] and <NAME2> [<ID2>] are related.\n` should be printed.  If there is a close family relationship (one of the five relationships described above), in addition, the following text should be printed: `<NAME1> [<ID1>] is the <TYPE-OF-RELATION> of <NAME2> [<ID2>].\n`

If it turns out that due to inbreeding, multiple close family relationships exist between two individuals all relationships should be listed line by line, sorted by the order of relationships in the list above. If the same type of relationship exists between the two individuals multiple times, the relationship should be listed only once. 

```
vsp> relationship 7 99
There is no relationship between Robb Stark [7] and Night King [99].

vsp> relationship 8 3
Sansa Stark [8] and Benjen Stark [3] are related.

vsp> relationship 7 8
Robb Stark [7] and Sansa Stark [8] are related.
Robb Stark [7] is the sibling of Sansa Stark [8].

vsp> 
```

##### Error Handling

The following errors must be handled (see [Return Values and Error Messages](#return-values-and-error-messages)) :

- The command was called with too many or too few parameters
- The given ID(s) do(es) not exist \
  The given ID is not an integer or could not be found in the program. \
  If both IDs do not exist, the error should be printed for the first ID.

***
</details>

<details>
<summary><h5>Command: prune</h5></summary>

- `prune`

In general, pruning a directed graph means removing some nodes to make the graph simpler. 

In our family tree, the task is to keep the graph as small as possible. Therefore, the prune command should ensure that all nodes in the graph that have no outgoing edges (= have no parents) are known persons. If a node that has no outgoing edges is an unknown person, this node should be removed completely (not only the name should be overwritten, but the whole node should be removed). These nodes should also not be listed by subsequent `list` commands (see Command: list).

For example, if the graph shown in the section DOT Files were pruned, the person “? [10]” would be removed.

This pruning process should be done recursively, as pruning a node may result in new prunable nodes.

If any nodes were pruned successfully, the text `Pruning was successful!\n` should be printed.

If no nodes were pruned, the text `Nothing to prune!\n` should be printed instead.

##### Error Handling

The following errors must be handled (see [Return Values and Error Messages](#return-values-and-error-messages)): 

- The command was called with too many or too few parameters

***
</details>

<details>
<summary><h5>Command: quit</h5></summary>

- `quit`

The `quit` command ends the program with the message `Bye.\n` and the return value 0.

##### Error Handling

The following errors must be handled (see [Return Values and Error Messages](#return-values-and-error-messages)): 
- The command was called with too many or too few parameters

***
</details>

<details>
<summary><h5>EOF</h5></summary>
Ends the program with return value 0 without a message.

***
</details>

</details>

</details>


## Return Values and Error Messages

The program has to react to errors and print the corresponding error messages and/or return the correct return values. You can find all error messages that should be printed and all return values in the table below.

Only one error should be printed at once. If multiple errors occur at the same time, only the highest message in the below table should be printed.

| Return Value | Error Message | Meaning |
| --- | --- | --- |
| 0 | - | The program terminated successfully |
| 1 | Usage: ./assignment [optional-input-file]\n | The program was called with an invalid number of command line parameters |
| 2 | Error: Out of memory.\n | The program was not able to allocate new memory |
| 3 | Error: Cannot open file.\n | The input file could not be opened for reading |
| 4 | Error: Invalid input file content.\n | The content of the DOT input file is invalid. |
| - | Error: Wrong parameter count.\n | The command was called with too many or too few parameters |
| - | Error: ID [\<ID>] does not exist. Use 'list' to find all available persons.\n | The given ID(s) do(es) not exist |
| - | Error: The given relation parameter does not exist.\n | The given relation does not exist |
| - | Error: Relationship already set.\n | Relationship already set |
| - | Error: Could not write file.\n | The program cannot write the desired output file |





## Examples

<details>
<summary><h4>Example 1</h4></summary>
The input file looks like this: 

```txt
digraph FamilyTree
{
  "Benjen Stark [3]" -> "Rickard Stark [1]";
  "Benjen Stark [3]" -> "Lyarra Stark [2]";
  "Eddard Stark [4]" -> "Rickard Stark [1]";
  "Eddard Stark [4]" -> "Lyarra Stark [2]";
  "Jon Snow [6]" -> "Eddard Stark [4]";
  "Jon Snow [6]" -> "? [10]";
  "Robb Stark [7]" -> "Catelyn Tully [5]";
  "Robb Stark [7]" -> "Eddard Stark [4]";
  "Sansa Stark [8]" -> "Eddard Stark [4]";
  "Sansa Stark [8]" -> "Catelyn Tully [5]";
  "Arya Stark [9]" -> "Eddard Stark [4]";
  "Arya Stark [9]" -> "Catelyn Tully [5]";
}
```
You can see the corresponding PNG image [here](https://dreampuf.github.io/GraphvizOnline/#digraph%20FamilyTree%0A%7B%0A%20%20%22Benjen%20Stark%20%5B3%5D%22%20-%3E%20%22Rickard%20Stark%20%5B1%5D%22%3B%0A%20%20%22Benjen%20Stark%20%5B3%5D%22%20-%3E%20%22Lyarra%20Stark%20%5B2%5D%22%3B%0A%20%20%22Eddard%20Stark%20%5B4%5D%22%20-%3E%20%22Rickard%20Stark%20%5B1%5D%22%3B%0A%20%20%22Eddard%20Stark%20%5B4%5D%22%20-%3E%20%22Lyarra%20Stark%20%5B2%5D%22%3B%0A%20%20%22Robb%20Stark%20%5B7%5D%22%20-%3E%20%22Catelyn%20Tully%20%5B5%5D%22%3B%0A%20%20%22Robb%20Stark%20%5B7%5D%22%20-%3E%20%22Eddard%20Stark%20%5B4%5D%22%3B%0A%20%20%22Jon%20Snow%20%5B6%5D%22%20-%3E%20%22Eddard%20Stark%20%5B4%5D%22%3B%0A%20%20%22Jon%20Snow%20%5B6%5D%22%20-%3E%20%22%3F%20%5B10%5D%22%3B%0A%20%20%22Sansa%20Stark%20%5B8%5D%22%20-%3E%20%22Eddard%20Stark%20%5B4%5D%22%3B%0A%20%20%22Sansa%20Stark%20%5B8%5D%22%20-%3E%20%22Catelyn%20Tully%20%5B5%5D%22%3B%0A%20%20%22Arya%20Stark%20%5B9%5D%22%20-%3E%20%22Eddard%20Stark%20%5B4%5D%22%3B%0A%20%20%22Arya%20Stark%20%5B9%5D%22%20-%3E%20%22Catelyn%20Tully%20%5B5%5D%22%3B%0A%7D).


This an example of the program output:
```
Welcome to the VSP Family Tree!

vsp> list
- Rickard Stark [1]
- Lyarra Stark [2]
- Benjen Stark [3]
- Eddard Stark [4]
- Catelyn Tully [5]
- Jon Snow [6]
- Robb Stark [7]
- Sansa Stark [8]
- Arya Stark [9]
- ? [10]
Persons with an asterisk (*) are not connected to any other person.

vsp> add Joffrey Baratheon
Successfully created Joffrey Baratheon [11]!

vsp> add Tywin Lannister
Successfully created Tywin Lannister [12]!

vsp> list
- Rickard Stark [1]
- Lyarra Stark [2]
- Benjen Stark [3]
- Eddard Stark [4]
- Catelyn Tully [5]
- Jon Snow [6]
- Robb Stark [7]
- Sansa Stark [8]
- Arya Stark [9]
- ? [10]
- Joffrey Baratheon [11]*
- Tywin Lannister [12]*
Persons with an asterisk (*) are not connected to any other person.

vsp> connect 12 parent1:gp1 11
Created unknown parent1 [13]!
Successfully connected Tywin Lannister [12] as parent1:gp1 of Joffrey Baratheon [11]!

vsp> list
- Rickard Stark [1]
- Lyarra Stark [2]
- Benjen Stark [3]
- Eddard Stark [4]
- Catelyn Tully [5]
- Jon Snow [6]
- Robb Stark [7]
- Sansa Stark [8]
- Arya Stark [9]
- ? [10]
- Joffrey Baratheon [11]
- Tywin Lannister [12]
- ? [13]
Persons with an asterisk (*) are not connected to any other person.

vsp> draw-all
  Benjen Stark [3] -> Rickard Stark [1]
  Benjen Stark [3] -> Lyarra Stark [2]
  Eddard Stark [4] -> Rickard Stark [1]
  Eddard Stark [4] -> Lyarra Stark [2]
  Jon Snow [6] -> Eddard Stark [4]
  Jon Snow [6] -> ? [10]
  Robb Stark [7] -> Catelyn Tully [5]
  Robb Stark [7] -> Eddard Stark [4]
  Sansa Stark [8] -> Eddard Stark [4]
  Sansa Stark [8] -> Catelyn Tully [5]
  Arya Stark [9] -> Eddard Stark [4]
  Arya Stark [9] -> Catelyn Tully [5]
  Joffrey Baratheon [11] -> ? [13]
  ? [13] -> Tywin Lannister [12]

vsp> rename 13 Cersei Lannister
Renaming ? [13] to Cersei Lannister [13] was successful!

vsp> list
- Rickard Stark [1]
- Lyarra Stark [2]
- Benjen Stark [3]
- Eddard Stark [4]
- Catelyn Tully [5]
- Jon Snow [6]
- Robb Stark [7]
- Sansa Stark [8]
- Arya Stark [9]
- ? [10]
- Joffrey Baratheon [11]
- Tywin Lannister [12]
- Cersei Lannister [13]
Persons with an asterisk (*) are not connected to any other person.

vsp> draw-all
  Benjen Stark [3] -> Rickard Stark [1]
  Benjen Stark [3] -> Lyarra Stark [2]
  Eddard Stark [4] -> Rickard Stark [1]
  Eddard Stark [4] -> Lyarra Stark [2]
  Jon Snow [6] -> Eddard Stark [4]
  Jon Snow [6] -> ? [10]
  Robb Stark [7] -> Catelyn Tully [5]
  Robb Stark [7] -> Eddard Stark [4]
  Sansa Stark [8] -> Eddard Stark [4]
  Sansa Stark [8] -> Catelyn Tully [5]
  Arya Stark [9] -> Eddard Stark [4]
  Arya Stark [9] -> Catelyn Tully [5]
  Joffrey Baratheon [11] -> Cersei Lannister [13]
  Cersei Lannister [13] -> Tywin Lannister [12]

vsp> relationship 11 4
There is no relationship between Joffrey Baratheon [11] and Eddard Stark [4].

vsp> relationship 11 13
Joffrey Baratheon [11] and Cersei Lannister [13] are related.
Joffrey Baratheon [11] is the child of Cersei Lannister [13].

vsp> delete 2
Deleting Lyarra Stark [2] was successful!

vsp> list
- Rickard Stark [1]
- ? [2]
- Benjen Stark [3]
- Eddard Stark [4]
- Catelyn Tully [5]
- Jon Snow [6]
- Robb Stark [7]
- Sansa Stark [8]
- Arya Stark [9]
- ? [10]
- Joffrey Baratheon [11]
- Tywin Lannister [12]
- Cersei Lannister [13]
Persons with an asterisk (*) are not connected to any other person.

vsp> prune
Pruning was successful!

vsp> list
- Rickard Stark [1]
- Benjen Stark [3]
- Eddard Stark [4]
- Catelyn Tully [5]
- Jon Snow [6]
- Robb Stark [7]
- Sansa Stark [8]
- Arya Stark [9]
- Joffrey Baratheon [11]
- Tywin Lannister [12]
- Cersei Lannister [13]
Persons with an asterisk (*) are not connected to any other person.

vsp> draw-all output
Creating DOT-file was successful!

vsp> quit
Bye.
```

The exported output.dot file looks like this:
```txt
digraph FamilyTree
{
  "Benjen Stark [3]" -> "Rickard Stark [1]";
  "Eddard Stark [4]" -> "Rickard Stark [1]";
  "Jon Snow [6]" -> "Eddard Stark [4]";
  "Robb Stark [7]" -> "Catelyn Tully [5]";
  "Robb Stark [7]" -> "Eddard Stark [4]";
  "Sansa Stark [8]" -> "Eddard Stark [4]";
  "Sansa Stark [8]" -> "Catelyn Tully [5]";
  "Arya Stark [9]" -> "Eddard Stark [4]";
  "Arya Stark [9]" -> "Catelyn Tully [5]";
  "Joffrey Baratheon [11]" -> "Cersei Lannister [13]";
  "Cersei Lannister [13]" -> "Tywin Lannister [12]";
}

```
You can see the corresponding PNG image [here](https://dreampuf.github.io/GraphvizOnline/#digraph%20FamilyTree%0A%7B%0A%20%20%22Benjen%20Stark%20%5B3%5D%22%20-%3E%20%22Rickard%20Stark%20%5B1%5D%22%3B%0A%20%20%22Eddard%20Stark%20%5B4%5D%22%20-%3E%20%22Rickard%20Stark%20%5B1%5D%22%3B%0A%20%20%22Robb%20Stark%20%5B7%5D%22%20-%3E%20%22Catelyn%20Tully%20%5B5%5D%22%3B%0A%20%20%22Robb%20Stark%20%5B7%5D%22%20-%3E%20%22Eddard%20Stark%20%5B4%5D%22%3B%0A%20%20%22Jon%20Snow%20%5B6%5D%22%20-%3E%20%22Eddard%20Stark%20%5B4%5D%22%3B%0A%20%20%22Sansa%20Stark%20%5B8%5D%22%20-%3E%20%22Eddard%20Stark%20%5B4%5D%22%3B%0A%20%20%22Sansa%20Stark%20%5B8%5D%22%20-%3E%20%22Catelyn%20Tully%20%5B5%5D%22%3B%0A%20%20%22Arya%20Stark%20%5B9%5D%22%20-%3E%20%22Eddard%20Stark%20%5B4%5D%22%3B%0A%20%20%22Arya%20Stark%20%5B9%5D%22%20-%3E%20%22Catelyn%20Tully%20%5B5%5D%22%3B%0A%20%20%22Joffrey%20Baratheon%20%5B11%5D%22%20-%3E%20%22Cersei%20Lannister%20%5B13%5D%22%3B%0A%20%20%22Cersei%20Lannister%20%5B13%5D%22%20-%3E%20%22Tywin%20Lannister%20%5B12%5D%22%3B%0A%7D).

***
</details>

