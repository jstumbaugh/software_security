# Project 1: Input Validator
### Jason Stumbaugh
### CSE 7359: Software Security

## Installation Instructions

To install the program, run `bundle install` to install the dependancies.

## Running the Phonebook

To run the phonebook, run `ruby input_validator.rb`

The rest is self explanitory.

### Acceptable Names

```
Bruce Schneier
Schneier, Bruce
Schneier, Bruce Wayne
O'Malley, John F.
Cher
James Ryan
Brad Everett Samuel Smith
Sammy Davis Jr.
Ron O'Henry
```

### Unacceptable Names

```
Ron O'Henry-Smith-Barnes
John O'Malley-Smith
L33t Hacker
<Script>alert(“XSS”)</Script>
select * from users;
```

### Acceptable Phone Numbers

```
123-456-7890
123.456.7890
123 456 7890
(123)456-7890
(123) 456-7890
(123)4567890
1234567890
11234567890
1 123 456 7890
1-123-456-7890
1 (123) 456-7890
+1 123 456-7890
+00 123 456 7890
```

### Unacceptable Phone Numbers

```
123
1/703/123/1234
Nr 102-123-1234
<script>alert(“XSS”)</script>
+1234 (201) 123-1234
(703) 123-1234 ext 204
```
