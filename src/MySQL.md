# MySQL

## MySQL的常见命令

```shell
#显示所有的数据库名
show databases; 
#进入一个数据库
use "数据库名" 
#显示当前库所有表名
show tables; 
#显示另一个数据库的所有表名
show tables from "表名"; 
#显示当前所在数据库名
select database(); 
#创建表
create table "表名"( 
id int,
name varchar(20));
# 显示表信息
desc "表名"; 
#查看数据库版本
select version();
```

## 注释

```mysql
单行注释
#注释文字
-- 注释文字
多行注释
/*注释文字*/
```

## SQL语言分类

- 数据查询语言DQL
- 数据操纵语言DML
- 数据定义语言DDL
- 数据控制语言DCL

## DQL

```mysql
##### 基础查询 #####
# 查询单个字段
SELECT 列名 FROM 表名 
# 查询多个字段
SELECT 列名1,列名2 FROM 表名
SELECT '列名1','列名2'FROM 表名
# 查询所有字段
SELECT * FROM 表名
# 查询常量值
SELECT 100
SELECT '22'
# 查询表达式
SELECT 20*8
# 查询函数值
SELECT VERSION()

# 起别名（别名有空格需要加''号）
SELECT 列名1 AS 别名1,列名2 AS 别名2 from 表名

# 去重
SELECT DISTINCT 列名 from 表名

# 连接
SELECT CONCAT(列名1,',',列名2) AS 别名 from 表名

# 判断空（如果第一个参数为空则返回第二个参数）
SELECT IFNULL(列名,新值) from 表名

##### 条件查询 #####
SELECT 查询列表 FROM 表名 WHERE  筛选条件
SELECT 查询列表 FROM 表名 WHERE  列名>100
SELECT 查询列表 FROM 表名 WHERE  列名=100
SELECT 查询列表 FROM 表名 WHERE  列名<>100
SELECT 查询列表 FROM 表名 WHERE  列名1>100 AND 列名2<100
SELECT 查询列表 FROM 表名 WHERE  NOT(列名>100)
SELECT 查询列表 FROM 表名 WHERE  列名1>100 OR 列名2>90

##### 模糊查询 #####
# 查询包含字符x的列
SELECT 查询列表 FROM 表名 WHERE 列名 LIKE '%x%'
# 查询第二个字符为x的列
SELECT 查询列表 FROM 表名 WHERE 列名 LIKE '_x%'

##### between and #####
SELECT 查询列表 FROM 表名 WHERE 列名 BETWEEN 值1 AND 值2

##### in #####
SELECT 查询列表 FROM 表名 WHERE 列名 IN(值1,值2,值3)

##### is null #####
SELECT 查询列表 FROM 表名 WHERE 列名 IS NULL
SELECT 查询列表 FROM 表名 WHERE ISNULL(列名)

##### <=> #####
SELECT * FROM 表名 WHERE 列名 <=> NULL

##### 排序查询 #####
# ASC是升序 DESC是降序
SELECT * FROM 表名 ORDER BY 列名 ASC
SELECT * FROM 表名 ORDER BY 列名 DESC
SELECT * FROM 表名 ORDER BY 列名1 DESC,列名2 ASC

##### 常见函数 #####
## 字符函数
# length获取字节数（汉字2个字节）
SELECT LENGTH(字符串)
# concat拼接字符串
SELECT CONCAT(字符串1,字符串2)
# upper、lower
SELECT UPPER("hh")
SELECT LOWER("HH")
# substr、substring
SELECT SUbSTR('ABCD',2)# 截取第2个字符后
SELECT SUbSTR('ABCD',2,1)# 截取第二个字符后一个字符
# instr
SELECT INSTR('ABCD',"C") # 返回C第一次出现的索引
# trim
SELECT TRIM("        HH     ")
# lpad、rpad
SELECT LPAD("HH",10,"*")# 左填充，HH位数不足10位左填充*
SELECT RPAD("HH",10,"*")
# replace
SELECT REPLACE("HHJJ","HH","KK")# 把HHJJ中的HH换成KK

## 数学函数
# round 四舍五入
SELECT ROUND(5.6)
SELECT ROUND(5.677,2)
# ceil 向上取整
SELECT CEIL(5.67)
# floor 向下取整
SELECT FLOOR(5.67)
# truncate 截断（去掉后面的）
SELECT TRUNCATE(5.67,1)
# mod 取余
SELECT MOD(5,2)

## 日期函数
# now 返回当前系统日期和时间
SELECT NOW()
# curdate 返回当前日期
SELECT CURDATE()
# curtime 返回当前时间
SELECT CURTIME()
# 年月日
SELECT YEAR(NOW())
SELECT MONTH(NOW())
SELECT MONTHNAME(NOW())
SELECT DAY(NOW())
SELECT HOUR(NOW())
SELECT MINUTE(NOW())
SELECT SECOND(NOW())
# str_to_date 字符转换日期
SELECT STR_TO_DATE('2000-11-21','%Y-%c-%d')
# date_format 日期转字符
SELECT DATE_FORMAT(NOW(),'%Y-%c-%d')

## 其他函数
SELECT VERSION()# 查看数据库版本
SELECT DATABASE()
SELECT USER()

## 流程控制函数
# if
SELECT IF(10>5,"YES","NO")
# case
SELECT CASE 变量
WHEN 常量1 操作1;
WHEN 常量2 操作1;
ELSE  操作3;
END

## 分组函数
sum、avg、max、min、count

##### 连接查询 #####
## 内连接
# 等值连接
SELECT 表1字段,表2字段 FROM 表1,表2 WHERE 表1字段=表2字段
# 非等值连接
SELECT 表1字段,表2字段 FROM 表1,表2 WHERE 表1字段 BETWEEN 表2字段 AND 表2字段
# 自连接
## 外连接
# 左外连接
# 右外连接
# 全外连接
## 交叉连接
```

## DML

```mysql
##### insert #####
INSERT into 表名(列名,列名...) values(值1...)
INSERT into 表名 values(值1...)

INSERT INTO 表名 set 列名=值,列名=值...
#方式一可以插入多行，支持子查询

##### update #####
UPDATE 表名 set 列=新值,列=新值... WHERE 查询条件

##### delete #####
DELETE FROM 表名 WHERE 查询条件
```

