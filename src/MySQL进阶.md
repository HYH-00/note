### 检索数据

#### 去重（DISTIONCT）

DISTINCT：distince可以过滤重复行，必须放在列名前面，对于多个列名，过滤的是所有列的组合

```mysql
SELECT DISTINCT col FROM table
```

####  限制结果（LIMIT）

```mysql
SELECT * FROM table LIMIT n
# 这样查询的是最旧的n条数据
SELECT * FROM table LIMIT m, n
# 查询的是第m条数据后的n条数据
```

####  排序结果（ORDER BY）

```mysql
SELECT * FROM table ORDER BY col
# 按col列查询数据，并按col排序展示
SELECT * FROM table ORDER BY col1, col2
# 也可以按多个列排序
SELECT * FROM table ORDER BY col DESC
# 排序默认是升序的ASC，如果需要降序排序，需要指定DESC参数
SELECT * FROM table ORDER BY col1 DESC, col2
# 多个列排序的时候DESC只对单独列生效
```

#### 过滤数据（WHERE）

```mysql
SELECT * FROM table WHERE col = value
# 查询所有指定列col的值等于value的行
SELECT * FROM table WHERE col1 = value1 AND col2 = value2
SELECT * FROM table WHERE col1 = value1 OR col2 = value2
# 可以有多个查询条件，条件间通过操作符AND、OR拼接
SELECT * FROM table WHERE col1 > value1 AND col2 < value2 AND col3 <> value3
SELECT * FROM table WHERE col IS NULL
SELECT * FROM table WHERE col IN (value1, value2, ...)
SELECT * FROM table WHERE NOE (col = value)
# 查询条件可以是=、>、<、!=、<>、<=、>=、BETWEEN、IS NULL、IN、NOT等等
```

**PS：**

- AND和OR优先级是不一样的，会优先计算AND

#### 通配符过滤（LIKE）

```mysql
SELECT * FROM table WHERE col LIKE 'xx%pp%jj_ll'
# %可以匹配任意数量的字符、_只匹配单个字符
```

#### 正则表达式（REGEXP）

```mysql
SELECT * FROM table WHERE col REGEXP BINARY '.val'
# 正则表达式使用关键字REGEXP，默认不区分大小写，可以使用BINARY指定，‘.’匹配一个字符
SELECT * FROM table WHERE col REGEXP '.val1｜.val2'
# 如果想匹配多个字符串用｜连接
SELECT * FROM table WHERE col REGEXP '[123]val'
# 如果想匹配某些字符串，用[]括起来，[]其实是[1|2|3]的缩写形式
SELECT * FROM table WHERE col REGEXP '[^123]val'
# 如果想匹配某些字符串外其他字符串使用[^123]
SELECT * FROM table WHERE col REGEXP '[^123]val'
# 如果想要匹配一个范围使用[1-3]
SELECT * FROM table WHERE col REGEXP '*val'
# 如果想要匹配0个或多个匹配使用*
# 1个或多个匹配使用+
# 1个或0个匹配使用?
# 指定数目的匹配{n}
# 指定不少于某个数量的匹配{n,}
# 匹配数目的范围{n,m}
# ……
```

#### 分组数据（GROUP BY & HAVING）

```mysql
SELECT id,COUNT(*) AS num FROM table GROUP BY id
# 查询不同id的数据条数并显示
SELECT id,COUNT(*) AS num FROM table WHERE id<val GROUP BY id HAVING COUNT(*)>2
# WHERE是在分组前进行过滤，HAVING在分组后进行过滤
```

#### 子查询

```mysql
SELECT * FROM table WHERE col1=val1 AND col2 IN (SELECT * FROM table WHERE col2=val2) 
# 子查询是从内向外进行查询的
```

#### 组合查询（UNION）

```mysql
SELECT col1,col2 FROM table1 WHERE col1=val1
UNION
SELECT col1,col2 FROM table2 WHERE col1=val1
# 组合查询默认去重，如果不想这么做，使用UNION ALL
# 组合查询结果可以排序，必须写在最后一个SELECT语句后，也不能使用多个排序函数
```

#### 全文本搜索（Match & Against）

```mysql
# 并不是所有的数据库引擎都支持全文本搜索，比如MySQL最常用的两个引擎MYISAM和InnoDB，前者支持，后者不支持
# 创建表的时候FULLTEXT(col)可以定义全文索引
# 定义全文索引后MySQL自动维护索引，增加、更新、删除行时索引自动更新
SELECT col FROM table WHERE Match(col) Against('xxx')
# 全文本搜索会以与文本匹配程度较好的顺序排序
```

