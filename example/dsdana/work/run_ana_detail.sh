#!/bin/sh

if [ $# -ne 1 ]; then
    echo "argv[1] = input file name"
    exit 1
fi

app="dsdana"
infile=$1
outfile=${infile/".root"/"_detailed_hittree.root"}
calfile=database.root

$app << EOF
define_analysis
5
-1
modify_param
full ok
$infile
eventtree
$calfile
dbtree
$outfile
hittree
analyze_data
read_data
-1
1000
exit
EOF
