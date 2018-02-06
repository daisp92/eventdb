#!/bin/bash

#create talbe, $3是命令行传过来的表名。
./create_table $3

#analyze
./dispatch $1 #dispatch分发，这个还没有实验。$1命令行传来的参数，表示存放root文件的目录。
mkdir $2 #创建$2表示的存放输出文件的目录。
mkdir $2/csv #创建$2/csv存放输出csv文件
mkdir $2/data
./run2data $1 $2 #分析root文件，为同一个run下的root文件建立事例倒排索引。确保$1目录下的root文件根据run号分发在对应的子文件下。

#insert，将csv和data两个子文件夹拷贝到hdfs:///eventdb/$3目录下
hadoop fs -copyFromLocal $2 /eventdb/$3

#bulkload，每一个数据表都有大量数据，使用hbase-bulkload批量导入。利用ImportTsv将csv文件导入到Hbase.HEP_$3为表的名字；导入到hdfs:///eventdb/$3/csv目录下
hbase org.apache.hadoop.hbase.mapreduce.ImportTsv -Dimporttsv.separator="," -Dimporttsv.columns="HBASE_ROW_KEY,data:run,data:offset,data:length,data:count" HEP_$3 hdfs:///eventdb/$3/csv
