#!/bin/sh

if [ $# -ne 1 ]; then
    echo "argv[1] = input file name"
    exit 1
fi

app="dsdana"
infile=$1
outfile=${infile/".root"/"_hittree.root"}
calfile=database.root

$app << EOF
modify_param
full ok
$calfile
dbtree
$infile
$outfile
yes#output lv1 branch
analyze_data
read_data
-1#number of event
1000#print frequency
exit
EOF
