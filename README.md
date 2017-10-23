# eventdb
高能物理百亿事例索引查询系统

## eventdb存储结构
![这里写图片描述](http://img.blog.csdn.net/20171023200529849?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvaGVsbG94aXl1ZQ==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/SouthEast)

## root分析
脚本./python/run2data分析root文件，同一个run下的root文件建立事例倒排索引。脚本支持多线程并行，命令格式：./run2data 'root-dir-path' 'save-dir-path' 'multiprocessing-num'

## hbase-bulkload导入
每一个数据表有50万行左右的数据，使用hbase-bulkload可以批量导入。命令格式：java -jar eventdb.jar org.osv.eventdb.CsvInsert 'hdfs-input-path' 'hdfs-output-path' 'hbase-table-name'

## eventdb查询
查询支持多个run查询，每个run号用逗号分隔。条件支持范围查询和交并运算。命令格式：./evtQuery -v 'hbase-table-name' -r 'runID' -q 'range(property1, min, max) && range(property2, min, max) || range(property3, min, max) ... ' -f 'output-file-name'