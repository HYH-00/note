# Redis

## 压力测试工具（官方自带）

**redis-benchmark**

| 选项  | 描述                                     | 默认值    |
| ----- | ---------------------------------------- | --------- |
| -h    | 指定服务器主机名                         | 127.0.0.1 |
| -p    | 指定服务器端口                           | 6379      |
| -s    | 指定服务器socket                         |           |
| -c    | 指定并发连接数                           | 50        |
| -n    | 指定请求数                               | 10000     |
| -d    | 以字节形式指定SET/GET值的数据大小        | 2         |
| -k    | 1=keep alive 0=reconnect                 | 1         |
| -r    | SET/GET/INCR 使用随机key SAADD使用随机值 |           |
| -P    | 通过管道传输\<numreq>请求                | 1         |
| -q    | 强制退出redis，仅显示query/sec值         |           |
| --csv | 以CSV格式输出                            |           |
| -I    | 生成循环，永久执行测试                   |           |
| -t    | 仅运行以逗号分隔的测试命令列表           |           |
| -l    | IDle模式。仅打开N个idle连接并等待        |           |

**创建100个并行的进程100000个请求测试redis**

```shell
redis-benchmark -h 127.0.0.1 -p 6379 -c 100 -n 100000
```

**测试结果**

```shell
====== PING_INLINE ======
  100000 requests completed in 1.96 seconds # 100000个请求消耗1.96秒
  100 parallel clients # 100个并行客户端
  3 bytes payload # 一次写入三个字节
  keep alive: 1 #一台服务器连接

58.78% <= 1 milliseconds # 第一秒处理58.78%
93.93% <= 2 milliseconds # 第二秒处理93.93%
98.55% <= 3 milliseconds
99.79% <= 4 milliseconds
100.00% <= 5 milliseconds
100.00% <= 5 milliseconds
51046.45 requests per second # 每秒处理51046.45个请求

....
```

**切换数据库**

```shell
# 有16个数据库，默认使用第0个
select 数字 #切换数据库，不太的数据库有不太的存储空间
DBSIZE # 查看DB大小

keys * # 查看所有的数据
flushdb # 清空当前数据库
flushall # 清空全部数据库
```



> Redis是单线程、C语言写的
>
> Redis是基于内存操作，CPU不是Redis的性能瓶颈。Redis的瓶颈是机器的内存和网络带宽
>
> 既然可以用单线程就用单线程了
>
> 官方提供的数据为100000+的QPS不比Memechche差

高性能的服务器不一定是多线程

多线程(CPU上下文会切换)不一定比单线程效率高

`核心：redis将所有的数据放在内存去操作，用单线程就是效率最高的`



## 常用命令

```shell
EXISTS name # 判断name这个键是否存在
move name 1 # 将name移动到数据库1
EXPIRE name 10 # 设置name10秒后过期
ttl name # 查看name过期时间 -2为过期
```



## 五大数据类型

### String

```shell
127.0.0.1:6379> set name hyh # 设置值
OK
127.0.0.1:6379> get name # 获取值
"hyh"
127.0.0.1:6379> keys * # 获取所有值
1) "name"
127.0.0.1:6379> exists name # 判断值是否存在
(integer) 1
127.0.0.1:6379> append name "kkkkk" # 在字符串后面拼接一些字符串
(integer) 8
127.0.0.1:6379> get name
"hyhkkkkk"
################################################
127.0.0.1:6379> set num 0
OK
127.0.0.1:6379> get num
"0"
127.0.0.1:6379> incr num # 值+1（只能对于数字使用）
(integer) 1
127.0.0.1:6379> get num
"1"
127.0.0.1:6379> decr num # 值-1
(integer) 0
127.0.0.1:6379> get num
"0"
127.0.0.1:6379> incrby num 10 # 值增加一个指定增量
(integer) 10
127.0.0.1:6379> get num
"10"
127.0.0.1:6379> decrby num 5 # 值减少一个值得增量
(integer) 5
127.0.0.1:6379> get num
"5"
###################################################
127.0.0.1:6379> set name hyh
OK
127.0.0.1:6379> get name
"hyh"
127.0.0.1:6379> getrange name 0 2 # 获取下表0到2的字符串
"hyh"
127.0.0.1:6379> getrange name 0 1
"hy"
127.0.0.1:6379> getrange name 0 -1 # 获取全部字符串
"hyh"
127.0.0.1:6379> setrange name 1 kkk #将下标为1后的字符串替换为kkk
(integer) 4
127.0.0.1:6379> get name
"hkkk"
###################################################
setex key time value # 设置生存时间（单位秒）
psetex key time value # 设置生存时间（单位毫秒）
setnx key time # 当键值不存在时才设置
getset key name # 设置值并返回旧值
strlen key # 返回值的长度，值不存在返回0
####################################################
mset key1 value1 key2 value2 # 批量设置
msetnx key1 value1 key2 value2 # 只有当所有键值都不存在才批量设置
mget key1 key2 # 批量获取值
```

### List

```shell
lpush key value # 左端插入
rpush key value # 右端插入
lrange key start end # 根据索引取出一段数据
lpop # 左端出栈
rpop # 右端出栈
lindex # 根据索引取出元素
lrem # 根据key删除指定元素
ltrim # 根据索引删除指定元素
rpoplpush # 移除列表另一个元素并添加到另一个列表并返回
lset # 根据index设置value
linsert before # 根据value在之前插入
linsert after # 根据value在之后插入
```

### Hash

```
hset
hsetnx
hget
hexists
hdel
hlen
hstrlen
hincrby
hincrbyfloat
hmset
hmget
hkeys
hvals
hgetall
hscan
```



### Sets

```shell
sadd
sismember
spop
srandmember
srem
smove
scard
smembers #返回所有成员
sscan
sinter #交
sinterstore
sunion #并
sunionstore
sdiff #差
sdiffstore
```

### ZSet

```shell
zadd
zscore
zincrby
zcard
zcount
zrange
zrevrange
zrangebyscore
zrebrangebyscore
zrank
zrevrank
zrem
zremrangebyrank
zremrangebyscore
zrangebylex
zlexcount
zremrangebylex
zscan
zunionstore
zinterstore
```

## 三种特殊数据类型

**Geospatial地理位置**

```
geoadd
geopos
geodist
geohash
georadius
georadiusbymember
zrem
```

**Hyperloglog**

```
pfadd
pfcount
pfmerge
```

**Bitmaps**

```
setbit
bitcount 
```

## 事务

Redis事务的本质：一组命令的集合！一个事务中的所有命令都会被序列化

一次性、顺序性、排他性，执行一系列命令

`Redis单条命令保持原子性，但是事务不保证原子性`

`Redis没有事务的隔离级别`

```shell
multi # 开启事务
#命令1
#命令2
exec # 结束
#discard取消事务
```

## 乐观锁

```shell
watch xx # watch监视变量，如果另外一个线程改变了xx事务会执行失败
# unwatch 解除监视
multi
...
...
exec
```

## Jedis

Java来操作Redis的工具

```java
//基本操作和原生redis命令类似
/*事务*/
Transaction multi=jedis.multi();

multi.exec();
```

## SpringBoot整合Redis

SpringBoot2.x之后原来使用的jedis替换为了lettuce

jedis：采用的直连，多个线程操作的话，是不安全的，如果要避免需要使用jedis pool连接池 更像BIO

lettuce：采用netty，实例可以在多个线程中进行共享

**依赖**

```xml

<!--使用Spring默认的RedisClient 也就是lettuce-->
<dependency>
    <groupId>org.springframework.boot</groupId>
    <!-- sb2.x后，这个从 spring-boot-starter-redis 改成下面的-->
    <artifactId>spring-boot-starter-data-redis</artifactId>
</dependency>

<!-- 集成redis连接池所需common-pool2，缺少了会报错 -->
<dependency>
    <groupId>org.apache.commons</groupId>
    <artifactId>commons-pool2</artifactId>
</dependency>



<!--使用jedis则-->
<dependency>
    <groupId>org.springframework.boot</groupId>
    <artifactId>spring-boot-starter-data-redis</artifactId>
    <!-- 必须要把lettuce移除掉，不让就算在application.yml中配置为jedis，也没效果 -->
    <exclusions>
        <exclusion>
            <artifactId>lettuce-core</artifactId>
            <groupId>io.lettuce</groupId>
        </exclusion>
    </exclusions>
</dependency>

<!--jedis - redis java 客户端-->
<dependency>
    <groupId>redis.clients</groupId>
    <artifactId>jedis</artifactId>
</dependency>

<!-- 集成redis连接池所需common-pool2，缺少了会报错 -->
<dependency>
    <groupId>org.apache.commons</groupId>
    <artifactId>commons-pool2</artifactId>
</dependency>
```

**application.yml**

```yml
redis:
        # 集群配置，暂时注释掉，以后有用到解开注释即可
#        cluster:
#          nodes:
#            - 127.0.0.1:7001
#            - 127.0.0.1:7002
#            - 127.0.0.1:7003
#            - 127.0.0.1:7004
#            - 127.0.0.1:7005
#            - 127.0.0.1:7006
          # 获取失败 最大重定向次数
#          max-redirects: 3

      # Redis数据库索引（默认为0）
        database: 1
        # Redis服务器地址，使用集群请注释掉
        host: 127.0.0.1
        # Redis服务器地址，使用集群请注释掉
        port: 6379
        # Redis服务器连接密码（默认为空）
        #password: 111111
        # 连接超时时间（毫秒）
        timeout: 3000000s
        lettuce:
            # 关闭超时时间
            shutdown-timeout: 100s
            ## redis线程池设置
            pool:
                # 连接池最大连接数（使用负值表示没有限制）
                max-active: 8
                # 连接池中的最大空闲连接
                max-idle: 8
                # 连接池最大阻塞等待时间（使用负值表示没有限制）
                max-wait: 1000000s
                # 连接池中的最小空闲连接
                min-idle: 1
         # jedis，如何你想使用jedis，则注释上面的Lettuce，打开这个注释即可
#        jedis:
#            pool:
#                # 连接池最大连接数（使用负值表示没有限制）
#                max-active: 8
#                # 连接池最大阻塞等待时间
#                max-wait: 1000000s
#                # 连接池中的最大空闲连接
#                max-idle: 8
#                # 连接池中的最小空闲连接
#                min-idle: 1
```



```
redisTemplate
opsForValue
opsForList
opsForSet
opsForHash
opsForZset
opsForGeo
opsForHyperLogLog
```

**redisconfig**

```java
package com.example.demo.config;

import com.fasterxml.jackson.annotation.JsonAutoDetect;
import com.fasterxml.jackson.annotation.PropertyAccessor;
import com.fasterxml.jackson.databind.ObjectMapper;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
import org.springframework.data.redis.connection.RedisConnectionFactory;
import org.springframework.data.redis.core.RedisTemplate;
import org.springframework.data.redis.serializer.Jackson2JsonRedisSerializer;
import org.springframework.data.redis.serializer.StringRedisSerializer;

@Configuration
public class RedisConfig {
    //自定义RedisTemplate
    @Bean
    @SuppressWarnings("all")
    public RedisTemplate<String, Object> myRedisTemplate(
            RedisConnectionFactory redisConnectionFactory) {
        //序列化配置
        Jackson2JsonRedisSerializer<Object> jackson2JsonRedisSerializer = new Jackson2JsonRedisSerializer<Object>(Object.class);
        ObjectMapper om = new ObjectMapper();
        om.setVisibility(PropertyAccessor.ALL, JsonAutoDetect.Visibility.ANY);
        om.enableDefaultTyping(ObjectMapper.DefaultTyping.NON_FINAL);
        jackson2JsonRedisSerializer.setObjectMapper(om);

        //String的序列化
        StringRedisSerializer stringRedisSerializer=new StringRedisSerializer();


        //自定义<String,Object>
        RedisTemplate<String, Object> template = new RedisTemplate<String, Object>();
        template.setConnectionFactory(redisConnectionFactory);

        template.setKeySerializer(stringRedisSerializer);
        template.setValueSerializer(jackson2JsonRedisSerializer);
        template.setHashKeySerializer(stringRedisSerializer);
        template.setHashValueSerializer(jackson2JsonRedisSerializer);
        template.afterPropertiesSet();
        return template;
    }
}
```

**RedisUtil**

```java
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.data.redis.core.RedisTemplate;
import org.springframework.stereotype.Component;
import org.springframework.util.CollectionUtils;
import java.util.List;
import java.util.Map;
import java.util.Set;
import java.util.concurrent.TimeUnit;

@Component
public final class RedisUtil {

    @Autowired
    private RedisTemplate<String, Object> redisTemplate;

    // =============================common============================
    /**
     * 指定缓存失效时间
     * @param key  键
     * @param time 时间(秒)
     */
    public boolean expire(String key, long time) {
        try {
            if (time > 0) {
                redisTemplate.expire(key, time, TimeUnit.SECONDS);
            }
            return true;
        } catch (Exception e) {
            e.printStackTrace();
            return false;
        }
    }
    /**
     * 根据key 获取过期时间
     * @param key 键 不能为null
     * @return 时间(秒) 返回0代表为永久有效
     */
    public long getExpire(String key) {
        return redisTemplate.getExpire(key, TimeUnit.SECONDS);
    }
    /**
     * 判断key是否存在
     * @param key 键
     * @return true 存在 false不存在
     */
    public boolean hasKey(String key) {
        try {
            return redisTemplate.hasKey(key);
        } catch (Exception e) {
            e.printStackTrace();
            return false;
        }
    }
    /**
     * 删除缓存
     * @param key 可以传一个值 或多个
     */
    @SuppressWarnings("unchecked")
    public void del(String... key) {
        if (key != null && key.length > 0) {
            if (key.length == 1) {
                redisTemplate.delete(key[0]);
            } else {
                redisTemplate.delete(CollectionUtils.arrayToList(key));
            }
        }
    }
    // ============================String=============================
    /**
     * 普通缓存获取
     * @param key 键
     * @return 值
     */
    public Object get(String key) {
        return key == null ? null : redisTemplate.opsForValue().get(key);
    }
    /**
     * 普通缓存放入
     * @param key   键
     * @param value 值
     * @return true成功 false失败
     */
    public boolean set(String key, Object value) {
        try {
            redisTemplate.opsForValue().set(key, value);
            return true;
        } catch (Exception e) {
            e.printStackTrace();
            return false;
        }
    }
    /**
     * 普通缓存放入并设置时间
     * @param key   键
     * @param value 值
     * @param time  时间(秒) time要大于0 如果time小于等于0 将设置无限期
     * @return true成功 false 失败
     */
    public boolean set(String key, Object value, long time) {
        try {
            if (time > 0) {
                redisTemplate.opsForValue().set(key, value, time, TimeUnit.SECONDS);
            } else {
                set(key, value);
            }
            return true;
        } catch (Exception e) {
            e.printStackTrace();
            return false;
        }
    }
    /**
     * 递增
     * @param key   键
     * @param delta 要增加几(大于0)
     */
    public long incr(String key, long delta) {
        if (delta < 0) {
            throw new RuntimeException("递增因子必须大于0");
        }
        return redisTemplate.opsForValue().increment(key, delta);
    }
    /**
     * 递减
     * @param key   键
     * @param delta 要减少几(小于0)
     */
    public long decr(String key, long delta) {
        if (delta < 0) {
            throw new RuntimeException("递减因子必须大于0");
        }
        return redisTemplate.opsForValue().increment(key, -delta);
    }
    // ================================Map=================================
    /**
     * HashGet
     * @param key  键 不能为null
     * @param item 项 不能为null
     */
    public Object hget(String key, String item) {
        return redisTemplate.opsForHash().get(key, item);
    }
    /**
     * 获取hashKey对应的所有键值
     * @param key 键
     * @return 对应的多个键值
     */
    public Map<Object, Object> hmget(String key) {
        return redisTemplate.opsForHash().entries(key);
    }
    /**
     * HashSet
     * @param key 键
     * @param map 对应多个键值
     */
    public boolean hmset(String key, Map<String, Object> map) {
        try {
            redisTemplate.opsForHash().putAll(key, map);
            return true;
        } catch (Exception e) {
            e.printStackTrace();
            return false;
        }
    }
    /**
     * HashSet 并设置时间
     * @param key  键
     * @param map  对应多个键值
     * @param time 时间(秒)
     * @return true成功 false失败
     */
    public boolean hmset(String key, Map<String, Object> map, long time) {
        try {
            redisTemplate.opsForHash().putAll(key, map);
            if (time > 0) {
                expire(key, time);
            }
            return true;
        } catch (Exception e) {
            e.printStackTrace();
            return false;
        }
    }
    /**
     * 向一张hash表中放入数据,如果不存在将创建
     *
     * @param key   键
     * @param item  项
     * @param value 值
     * @return true 成功 false失败
     */
    public boolean hset(String key, String item, Object value) {
        try {
            redisTemplate.opsForHash().put(key, item, value);
            return true;
        } catch (Exception e) {
            e.printStackTrace();
            return false;
        }
    }
    /**
     * 向一张hash表中放入数据,如果不存在将创建
     *
     * @param key   键
     * @param item  项
     * @param value 值
     * @param time  时间(秒) 注意:如果已存在的hash表有时间,这里将会替换原有的时间
     * @return true 成功 false失败
     */
    public boolean hset(String key, String item, Object value, long time) {
        try {
            redisTemplate.opsForHash().put(key, item, value);
            if (time > 0) {
                expire(key, time);
            }
            return true;
        } catch (Exception e) {
            e.printStackTrace();
            return false;
        }
    }
    /**
     * 删除hash表中的值
     *
     * @param key  键 不能为null
     * @param item 项 可以使多个 不能为null
     */
    public void hdel(String key, Object... item) {
        redisTemplate.opsForHash().delete(key, item);
    }
    /**
     * 判断hash表中是否有该项的值
     *
     * @param key  键 不能为null
     * @param item 项 不能为null
     * @return true 存在 false不存在
     */
    public boolean hHasKey(String key, String item) {
        return redisTemplate.opsForHash().hasKey(key, item);
    }
    /**
     * hash递增 如果不存在,就会创建一个 并把新增后的值返回
     *
     * @param key  键
     * @param item 项
     * @param by   要增加几(大于0)
     */
    public double hincr(String key, String item, double by) {
        return redisTemplate.opsForHash().increment(key, item, by);
    }
    /**
     * hash递减
     *
     * @param key  键
     * @param item 项
     * @param by   要减少记(小于0)
     */
    public double hdecr(String key, String item, double by) {
        return redisTemplate.opsForHash().increment(key, item, -by);
    }
    // ============================set=============================
    /**
     * 根据key获取Set中的所有值
     * @param key 键
     */
    public Set<Object> sGet(String key) {
        try {
            return redisTemplate.opsForSet().members(key);
        } catch (Exception e) {
            e.printStackTrace();
            return null;
        }
    }
    /**
     * 根据value从一个set中查询,是否存在
     *
     * @param key   键
     * @param value 值
     * @return true 存在 false不存在
     */
    public boolean sHasKey(String key, Object value) {
        try {
            return redisTemplate.opsForSet().isMember(key, value);
        } catch (Exception e) {
            e.printStackTrace();
            return false;
        }
    }
    /**
     * 将数据放入set缓存
     *
     * @param key    键
     * @param values 值 可以是多个
     * @return 成功个数
     */
    public long sSet(String key, Object... values) {
        try {
            return redisTemplate.opsForSet().add(key, values);
        } catch (Exception e) {
            e.printStackTrace();
            return 0;
        }
    }
    /**
     * 将set数据放入缓存
     *
     * @param key    键
     * @param time   时间(秒)
     * @param values 值 可以是多个
     * @return 成功个数
     */
    public long sSetAndTime(String key, long time, Object... values) {
        try {
            Long count = redisTemplate.opsForSet().add(key, values);
            if (time > 0)
                expire(key, time);
            return count;
        } catch (Exception e) {
            e.printStackTrace();
            return 0;
        }
    }
    /**
     * 获取set缓存的长度
     *
     * @param key 键
     */
    public long sGetSetSize(String key) {
        try {
            return redisTemplate.opsForSet().size(key);
        } catch (Exception e) {
            e.printStackTrace();
            return 0;
        }
    }
    /**
     * 移除值为value的
     *
     * @param key    键
     * @param values 值 可以是多个
     * @return 移除的个数
     */
    public long setRemove(String key, Object... values) {
        try {
            Long count = redisTemplate.opsForSet().remove(key, values);
            return count;
        } catch (Exception e) {
            e.printStackTrace();
            return 0;
        }
    }
    // ===============================list=================================
    /**
     * 获取list缓存的内容
     *
     * @param key   键
     * @param start 开始
     * @param end   结束 0 到 -1代表所有值
     */
    public List<Object> lGet(String key, long start, long end) {
        try {
            return redisTemplate.opsForList().range(key, start, end);
        } catch (Exception e) {
            e.printStackTrace();
            return null;
        }
    }
    /**
     * 获取list缓存的长度
     *
     * @param key 键
     */
    public long lGetListSize(String key) {
        try {
            return redisTemplate.opsForList().size(key);
        } catch (Exception e) {
            e.printStackTrace();
            return 0;
        }
    }
    /**
     * 通过索引 获取list中的值
     *
     * @param key   键
     * @param index 索引 index>=0时， 0 表头，1 第二个元素，依次类推；index<0时，-1，表尾，-2倒数第二个元素，依次类推
     */
    public Object lGetIndex(String key, long index) {
        try {
            return redisTemplate.opsForList().index(key, index);
        } catch (Exception e) {
            e.printStackTrace();
            return null;
        }
    }
    /**
     * 将list放入缓存
     *
     * @param key   键
     * @param value 值
     */
    public boolean lSet(String key, Object value) {
        try {
            redisTemplate.opsForList().rightPush(key, value);
            return true;
        } catch (Exception e) {
            e.printStackTrace();
            return false;
        }
    }
    /**
     * 将list放入缓存
     * @param key   键
     * @param value 值
     * @param time  时间(秒)
     */
    public boolean lSet(String key, Object value, long time) {
        try {
            redisTemplate.opsForList().rightPush(key, value);
            if (time > 0)
                expire(key, time);
            return true;
        } catch (Exception e) {
            e.printStackTrace();
            return false;
        }

    }
    /**
     * 将list放入缓存
     *
     * @param key   键
     * @param value 值
     * @return
     */
    public boolean lSet(String key, List<Object> value) {
        try {
            redisTemplate.opsForList().rightPushAll(key, value);
            return true;
        } catch (Exception e) {
            e.printStackTrace();
            return false;
        }

    }
    /**
     * 将list放入缓存
     *
     * @param key   键
     * @param value 值
     * @param time  时间(秒)
     * @return
     */
    public boolean lSet(String key, List<Object> value, long time) {
        try {
            redisTemplate.opsForList().rightPushAll(key, value);
            if (time > 0)
                expire(key, time);
            return true;
        } catch (Exception e) {
            e.printStackTrace();
            return false;
        }
    }
    /**
     * 根据索引修改list中的某条数据
     *
     * @param key   键
     * @param index 索引
     * @param value 值
     * @return
     */
    public boolean lUpdateIndex(String key, long index, Object value) {
        try {
            redisTemplate.opsForList().set(key, index, value);
            return true;
        } catch (Exception e) {
            e.printStackTrace();
            return false;
        }
    }
    /**
     * 移除N个值为value
     *
     * @param key   键
     * @param count 移除多少个
     * @param value 值
     * @return 移除的个数
     */
    public long lRemove(String key, long count, Object value) {
        try {
            Long remove = redisTemplate.opsForList().remove(key, count, value);
            return remove;
        } catch (Exception e) {
            e.printStackTrace();
            return 0;
        }

    }
}
```

## Redis配置文件


```shell
#####################网络
bind 127.0.0.1 # 绑定
protected-mode yes # 保护模式
port 6379 # 端口
######################通用GENERAL
daemonize yes # 以守护进程的方式运行，默认为no
pidfile /var/run/redis.pid # 如果以后台方式运行需要指定一个pid文件

#日志
loglevel notice
logfile "" # 日志的文件位置名
databases 16 # 数据库数量 默认16个
#######################快照
# Redis是内存数据库，没有持久化，数据断电丢失
save 900 1 #900秒内至少有一个key修改就进行持久化操作
save 300 10 #300秒内超过10个key修改进行持久化
save 60 10000 #60秒内有10000个key修改进行持久化
stop-writes-on-bgsave-error yes #持久化出错是否继续工作
rdbcompression yes #是否压缩rdb文件，需要消耗一些cpu资源
rdbchecksum yes #保存rdb文件是否进行校验
dbfilename dump.rdb #rdb保存目录
########################复制REPLICATION
########################安全SECURITY
requirepass foobared #密码
#命令行
config get requirepass #查看密码
config set requirepass 新密码 # 设置密码
auth 密码 #登录
##########################限制LIMITS
maxclients 10000 #最多客户端数
maxmemory <bytes> #最大内存
maxmemory-policy noeviction #内存到达上限的处理策略
	#移除一些过期的key
	#报错
	1、volatile-lru：只对设置了过期时间的key进行LRU（默认值） 
	2、allkeys-lru ： 删除lru算法的key   
	3、volatile-random：随机删除即将过期key   
	4、allkeys-random：随机删除   
	5、volatile-ttl ： 删除即将过期的   
	6、noeviction ： 永不过期，返回错误
#########################AOF配置APPEND ONLY MODE
appendonly no #默认不开启aof默认使用rdb方式持久化（一般情况rdb够用）
appendfilename "appendonly.aof" #aof持久化文件

# appendfsync always #每次修改都会sync
appendfsync everysec #每秒执行一次sync，可能会丢失1s数据
# appendfsync no # 不执行sync，由操作系统自己进行同步
```

## Redis持久化

### RDB（Redis DateBase）

在指定时间间隔内将内存中的数据集快照写入磁盘，Snapshot快照，恢复时将快照文件直接读到内存

报错快照是由子进行完成，将内存写入临时的edb文件，快照写入完成后覆盖原先的快照文件

`如果进行大规模的数据恢复或者对数据完整性要求不高，edb比aof更高效，缺点的可能丢失最后一次持久化的数据`

rdb保存的文件是dump.rdb

> 触发机制

- save规则满足
  - 自动触发最常见的情况是在配置文件中通过save m n，指定当m秒内发生n次变化时，会自动触发bgsave

- flushall命令会触发
- 退出redis

Redis启动时自动检查是否有rdb文件

查看存在位置

```
config get dir
```

**缺点**

- 需要一定的时间间隔，如果意外宕机，最后一次修改数据就丢失
- fork进程，会占用一定内存空间

**优点**

- 适合大规模的数据恢复
- 对数据完整性要求不高

### AOF（Append Only File）

以日志的形式记录每一个写的操作，将所有执行过的指令记录下来（读操作不记录）

- 每秒同步
- 修改同步
- 不同步

redis重启的话会根据日志文件的内容将写指令从前到后执行一遍完成数据恢复

aof文件被改动，redis是启动不起来的，需要用redis-check-aof --fix

**缺点**

- 相对于数据文件来说，aof远大于rdb，所以aof比rdb慢

**优点**

- 每次修改都同步，文件完整性会更加好
- 每秒同步一次，可能丢失数据
- 从不同步效率更高

## 发布订阅

一种消息通信模式：发送者pub发送消息，订阅者sub接收消息

组成：消息发送者、频道、消息订阅者

```shell
psubscribe paterm[paterm...] #订阅一个或多个符合给定模式的频道
pubsub subcommand #查看订阅与发布系统的状态
publish channel message #将信息发送到指定频道
punsubscribe pattern #退订所有给定模式的频道
subscribe channel[channel...] #订阅一个或多个给定频道的信息
unsubscribe [channel[channel..]] #退订给定频道
```

## 主从复制

一台Redis服务器的数据复制到其他服务器，主机以写为主，从机以读为主（写比较少，读较多）

### 作用

- 数据冗余：主从复制实习了数据的热备份，是持久化之外的一种数据冗余方式
- 故障恢复：当主节点出现问题时，可以由从节点提供服务，相当于一个服务的冗余
- 负载均衡：在主从复制的基础上实现读写分离
- 高可用（集群）基石：是哨兵和集群能够实施的基础

### 配置

```shell
#查看当前库的信息
info replication

#配置多个配置文件，更改信息
#更改pid端口名
#更改pidfile名
#更改logfiel名
#更改dbfilename名

#启动服务
redis-server 配置名.conf
```

默认情况每一个redis都是一个主节点，配置时只需要配置从机

```shell
#认主机（命令是暂时的）
slaveof 127.0.0.1 6379

#永久的主从配置需要改配置文件（windows）
# slaveof <masterip> <masterport>
# replicaof <masterip> <masterport>
```

主机可以写，从机不能写，主机写的东西从机会自动保存



如果主机宕机，从机还是从机模式，主机再次连接，从机还是可以再次连接



命令行配置的主从复制如果从机宕机，再次连接，从机自动变成主机，不能获取从机状态值，变回从机可以获取

因为第一次连接主机的适合会全量复制

```shell
slaveof no one #更改当前为主机
#如果老大上线，重新连接
```

## 哨兵模式

> 自动选举老大

监控后台主机是否故障，故障了根据投票数自动将票数最高的从机变为主机

redis-sentinel

通常哨兵需要集群，防止哨兵宕机

`当一个哨兵模式发现主机不可用，称为主观下线，当多数哨兵都发现不可用时会进行投票选举主机，称为客观下线`

```shell
#哨兵配置文件sentinel monitor 被监控名称 host port 1
sentinel monitor myredis 127.0.0.1 6379
```

主机回来只能归并到新的主机下，当作从机

### 优点

- 哨兵集群，基于主从复制模式，所有的主从配置优点，全有
- 主从可以切换，故障可以转移，可用性更好
- 哨兵模式是主从模式的升级，手动到自动

### 缺点

- 不好在线扩容，集群容量达到上限在线扩容就很麻烦
- 哨兵模式配置复杂

## Redis缓存穿透和雪崩

### 缓存穿透

redis内存数据库没有，缓存未命中，会向持久层数据库请求，当请求很多的时候会导致持久层数据库崩溃

#### 解决方案

**布隆过滤器**

对可以查询的参数以hash形式存储，在控制层校验，不符合则丢弃，避免了对底层存储系统的压力

- 节约空间
- 保密性好
- 存在误判
- 不能删除布隆过滤器中的元素

**缓存空对象**

缓存不命中，返回一个空值，空值也会被储存起来

### 缓存击穿

很热的key在过期后同时请求数据库（并发查同一个数据）

#### 解决方案

**设置热点数据永不过期**

**加互斥锁**

分布式锁，每一个key只有一个进程能够查询

> 分布式锁
>
> - 基于数据库实现分布式锁
>   - 插入数据表示加锁（唯一性约束）
>   - 删除数据表示释放锁
> - 基于缓存（如Redis）实现分布式锁
> - 基于Zookeeper实现分布式锁
>   - ZooKeeper是一个为分布式应用提供一致性服务的开源组件，它内部是一个分层的文件系统目录树结构，规定同一个目录下只能有一个唯一文件名

### 缓存雪崩

某一个时间段，缓存集中过期失效，Redis宕机（很多数据过期）

#### 解决方案

**redis高可用（异地多活）**

**限流降级**

**数据预热**

**过期时间打散**