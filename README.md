# NetCoffee2

################################################################################

PROGRAM:NetCoffee2

AUTHOR:JIALU HU and JUNHAO HE

EMAIL: jialu.hu@fu-berlin.de  hejunhao@mail.nwpu.edu.cn

Copyright (C++) <2017>  <Junhao He>


This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

################################################################################

Description
This file is README file of the package of NetCoffee2, developed by Junhao He.
To guide you quickly starting to use our alignment tool, we structured this README into four parts:

1) PREREQUISITE
2) COMPILING
3) OPTION
4) EXAMPLE
Before running this program, you are strongly recommended to read this file carefully.

################################################################################

PREREQUISITE

Igraph-0.7.1
Igraph is a collection of network analysis tools with the emphasis on efficiency,portablity and ease of use. Igraph is open source and free.
The source code is freely available at website: http://igraph.org/c/#downloads.
Please first install igraph before compiling the code of NetCoffee2.
For detials in website: http://igraph.org/c/

################################################################################

COMPLING

To compile the source code, the latest compilers which supports the standard language C++11, also known as C++0x, is needed. Other older compiler may not support it.
cd $NETCOFFEE2
./make MODE=Release
#If you want to compile it in Debug mode, run command:
./make (MODE=Debug)

################################################################################

OPTION

You can see the detailed option information with option "-help".
It is noted that there are four options you must specify if you want to run NetCoffee2 for an alignment task. They are described as follows:

1. -inputnet

This option specifies the file name of several networks you want to align.
It is ecpected to be in three-column tab-delimited format.
First column: netID
second column: interactorA
third column: interactorB
For example, suppose we have three PPI networks:homoSapiens, MusMusculus,DrosophilaMelanogaster. The inputnet file should looks like:

-----------------------BEGIN OF INPUTNET---------------------

HomoSapiens	P62633	Q00577
HomoSapiens	Q9GZT8	Q2VPB7
HomoSapiens	O95602	P04626
HomoSapiens	P56524	Q08379
MusMusculus	P10605	P11438
MusMusculus	P03966	Q6PDN3
MusMusculus	Q9DBY1	P57716
MusMusculus	Q9WUD1	Q61083
DroMelanogaster	Q7KSX2	Q7KSX2
DroMelanogaster	Q9VKA1	Q9VX51
DroMelanogaster	Q9BN17	Q9VD53
DroMelanogaster	O61492	A1ZAZ2

-------------------------END OF INPUTNET----------------------

2. -inputbit

This option specifies the blastp sequence similarity files for each pair of species, which includes three columns seperated by <TAB>.
The first column provides proteins from the first netwoks, the second column provides proteins from the second networks, the third column provides bitscore.
Here is an example:

--------------BEGIN OF BITSCORE FILE--------------

P31946	P62258	  325.0
P31946	Q04917	  367.0
P31946	P61981	  373.0
P31946	P31947	  340.0
P31946	P27348	  416.0
P31946	P63104	  441.0
P62258	P31946	  325.0
P62258	P62258	  524.0
P62258	Q04917	  309.0
P62258	P61981	  315.0

--------------END OF BITSCORE FILE--------------

3. -numnet

This option tell program how many networks you want to align.

4. -output

This option tell program the name and path of result of alignment and alignment score, by default, it is in result folder

5. other option in Usage

You can generate the follow message by running the program with option "-help"

$NETCOFFEE2/bin/NetCoffee2 -help
USAGE: NetCoffee2  [-help] [-beta DOUBLE] [-version] -numnet INTEGER -inputbit STRING -inputnet STRING -output STRING [-alph DOUBLE]
DESCRIPTION: An application for multiple global network alignment.
VERSION: NetCoffee2 1.0.006
ALL MANDATORY AND OPTIONAL ARGUMENTS:
-help   Show help information.
-beta   beta used for the rate of conserved protein in a same network
-version        Show the current version.
-numnet A mandatory option. The number of ppi networks
-inputbit       A mandatory option. The path of an input file.
-inputnet       A mandatory option. The path of an input file.
-output A mandatory option. The path of an output file.
-alph   alph for sequence and topology similarity


################################################################################

EXAMPLE

1. Download dataset

Our datasets are freely available at our website: http://www.nwpu-bioinformatics.com/
Download it into the folder of $NETCOFFEE2 and uncompress it with command:
tar -zxvf dataset.tar.gz

2. Dataset Description

By download dataset in our website, you will have three test data, two of which have three real PPI networks(test1, test2). and the other is a simple example of two small nets for NetCoffee2(test_sample).
3. Compile source code

Compile the source code with command:
make MODE=Release

4. Run NetCoffee2 on our test dataset with commend:

./NetCoffee2 -inputnet ./testdata/test2/int_net_test2.txt -inputbit ./testdata/test2/int_bit_test2.txt -output "alignmentResule.txt" -numnet 3
Then you can find the alignment result and alignment score in result folder.
There are many other functions which you can see with "-help" option

################################################################################

END
THANK FOR READING
If you have any questions regarding to the program, please don't hesitate to contact us through email.

