# qvfin

Finds all mutation-finite quivers of a certain size.

### Usage

```
qvfin [size] [options]
```

The size option specifies what size of mutation-finite quiver should be
generated. This should be an integer greater than or equal to 2.

The options are passed through to `qvtrim`. See the [qvtrim readme][qvtrim site]
for details of what options are valid. Ensure that the options are contained
within quotes, so bash does not split them up.

##### Examples

```
qvfin 5 "-o ~/output"
```
Find all 5 vertex mutation-finite quivers and output them to the file
`~/output`.

```
qvfin 8 -g
```
Find all 8 vertex mutation-finite quivers and print to stdout only those which
have different underlying graphs.

### Structure

`qvfin` is a bash script which depends on the following programs:

 * qvfex
 * qvtrim

`qvfex` is included in this repo, see [Build](#build) section for details of
compiling it.

`qvtrim` is included in the [qvtrim repo][qvtrim site]. This program should be
installed on the path or in the same folder as `qvfin`, so that the script can
find it.

### Build<a name="build"></a>

`qvfex` can be built by running `make`.

##### Dependencies

`qvfex` requires the following library and its headers to be installed and
accessible by the compiler:

 * [libqv][libqv site]

The Makefile can be modified to include the install locations of these
libraries, by changing the `INCLUDES` and `LFLAGS` variables.


### License

```
   Copyright 2014-2015 John Lawson

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
```

[qvtrim site]: http://github.com/jwlawson/qvtrim
[libqv site]: http://github.com/jwlawson/qv
