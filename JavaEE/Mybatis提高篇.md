# Mybatis提高篇

[TOC]

## insert元素主键回填

```xml
<insert id="addUser" parameterType="com.hnucm.springboot.pojo.User"
        useGeneratedKeys="true" keyProperty="id">
    insert into user (name,age) values (#{name},#{age})
</insert>
```

使用useGeneratedKeys=“true”来获取有数据库内部生成的主键

使用keyProperty来指定哪个是主键字段

插入后会自动填充主键



## 使用自定义规则生成主键

实际工作上有时候主键的生成规则并不是这么简单，比如我们取消t_user的主键自增规则。我们的要求是：

如果t_user表没有数据，我们也要设置主键为1，否则就取主键最大值加2，来设置新的主键。

对此，Mybatis也提供了处理方法，使用SelectKey元素进行处理

```xml
<insert id="insertUser" parameterType="user" useGeneratedKeys="true" keProperty="id">
	<SelectKey keProperty="id" resultType="int" order="BEFORE>
		select if(max(id) is null, 1, max(id) + 2) as newId from t_user
	</SelectKey>
	insert into t_user(user_name,age) values (#${userName},#{age})
</insert>
```





## resultMap

>`resultMap`是`Mybatis`映射文件中最重要最强大的元素。它描述如何从结果集中加载对象，主要作用是定义映射规则、级联的更新、定制类型转化器。它可以让你从 90% 的 JDBC ResultSets 数据提取代码中解放出来, 并在一些情形下允许你做一些 JDBC 不支持的事情。 实际上，在对复杂语句进行联合映射的时候，它很可能可以代替数千行的同等功能的代码。 resultMap的设计思想是，简单的语句不需要明确的结果映射，而复杂一点的语句只需要描述它们的关系就行了。

**resultType元素**

使用resultType进行输出映射，只有查询出来的列名和pojo（实体bean）中的属性名一致，该列才可以映射成功。简单来说也就是你的数据库字段和JavaBean里的字段名称必须一致才能映射成功。

**resultMap映射结果集**

```xml
select id="getUser" resultMap="userResult">
    select * from user ;
</select>
<resultMap id="userResult" type="com.hnucm.springboot.pojo.User">
    <id property="id" column="id"/>
    <result property="name1" column="name"/>
    <result property="age" column="age"/>
</resultMap>
```



## 一对一级联查询

应用场景举例：人与身份证之间的关系为一对一，即一个人只能拥有一个身份证，一个身份证只能对应一个人。

创建`idcard`表和`person`表



### Dao

```java
@Mapper
public interface IdCardMapper {
    IdCard findCardById(int id );
    int addIdcard(IdCard idCard);
}

```



```java
@Mapper
public interface PersonMapper {
    Person findPersonById(int id);

    List<Person> findAllPerson();

    int addPerson(Person person);
}

```







### Mapper文件

**IdCardMapper.xml**

```xml
<?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE mapper PUBLIC "-//mybatis.org//DTD Mapper 3.0//EN" "http://mybatis.org/dtd/mybatis-3-mapper.dtd">
<mapper namespace="com.hnucm.springboot.demo.dao.IdCardMapper">
    <select id="findCardById" resultType="com.hnucm.springboot.demo.pojo.IdCard"
            parameterType="Integer">
        select  * from idcard where id = #{id}
    </select>
    <insert id="addIdcard" parameterType="com.hnucm.springboot.demo.pojo.IdCard"
            useGeneratedKeys="true" keyProperty="id">
        insert  into idcard (code) values (#{code})
    </insert>
</mapper>

```





**PersonMapper.xml**

```xml
<?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE mapper PUBLIC "-//mybatis.org//DTD Mapper 3.0//EN" "http://mybatis.org/dtd/mybatis-3-mapper.dtd">
<mapper namespace="com.hnucm.springboot.demo.dao.PersonMapper">

    <resultMap id="cardAndPerson" type="com.hnucm.springboot.demo.pojo.Person">
        <id property="id" column="id"></id>
        <result property="name" column="name"/>
        <result property="age" column="age"/>
        <association property="idcard" column="idcard_id"
                     javaType="com.hnucm.springboot.demo.pojo.IdCard"
                     select="com.hnucm.springboot.demo.dao.IdCardMapper.findCardById">
        </association>
    </resultMap>

    <select id="findAllPerson" resultMap="cardAndPerson">
        select * from person;
    </select>

    <select id="findPersonById" resultMap="cardAndPerson"
            parameterType="Integer">
        select  * from person where id = #{id}
    </select>
    <insert id="addPerson" parameterType="com.hnucm.springboot.demo.pojo.Person">
    insert  into person (name ,age ,idcard_id) values (#{name},#{age},#{idcard.id})
</insert>

</mapper>

```





### Service

PersonSercvie

```java
package com.hnucm.springboot.demo.service.impl;

import com.hnucm.springboot.demo.dao.IdCardMapper;
import com.hnucm.springboot.demo.dao.PersonMapper;
import com.hnucm.springboot.demo.pojo.IdCard;
import com.hnucm.springboot.demo.pojo.Person;
import com.hnucm.springboot.demo.service.PersonService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import java.util.List;

@Service
public class PersonServiceImpl implements PersonService {
    @Autowired
    PersonMapper personMapper;

    @Autowired
    IdCardMapper idCardMapper;
    @Override
    public Person findPersonById(int id) {
        return personMapper.findPersonById(id);
    }

    @Override
    public List<Person> findAllPerson() {
        return personMapper.findAllPerson();
    }

    @Transactional
    @Override
    public int addPerson(Person person) {
        int result = idCardMapper.addIdcard(person.getIdcard());
        if (result > 0) {
          return   personMapper.addPerson(person);
        }
        return 0;
    }
}
```





```java
package com.hnucm.springboot.demo.controller;

import com.hnucm.springboot.demo.pojo.Person;
import com.hnucm.springboot.demo.pojo.Result;
import com.hnucm.springboot.demo.pojo.User;
import com.hnucm.springboot.demo.service.PersonService;
import com.hnucm.springboot.demo.service.UserService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;

@RestController
@CrossOrigin
public class PersonController {

    @Autowired
    PersonService personService;
    @RequestMapping("getperson")
    public Result getperson(){
        return  Result.ok().put("data",personService.findAllPerson());
    }
    @RequestMapping("getperson/{id}")
    public Result getuserbyid(@PathVariable int id) {
        return Result.ok().put("data",personService.findPersonById(id));
    }
    @RequestMapping("addperson")
    public Result addperson(@RequestBody Person person) {
        return Result.ok().put("data",personService.addPerson(person)>0?"添加成功":"添加失败");
    }

}
```





```java
@Data
public class Person {
    private int id;
    private String name;
    private int age;
    private IdCard idcard;
}
```







## 一对多级联查询

应用场景举例：用户与订单之间的关系为一对多，即一个用户可以有多个订单，而一个订单只属于一个用户

### Mapper

UserMapper.xml

```xml
<?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE mapper PUBLIC "-//mybatis.org//DTD Mapper 3.0//EN" "http://mybatis.org/dtd/mybatis-3-mapper.dtd">
<mapper namespace="com.hnucm.springboot.demo.dao.UserMapper">
    <resultMap id="orderandUser" type="com.hnucm.springboot.demo.pojo.User">
        <id property="id" column="id"></id>
        <!--ofType表示集合的元素类型，将id传递给Dao接口中的findOrdersByUserId方法-->
        <collection property="orderList"
                    select="com.hnucm.springboot.demo.dao.OrderMapper.findOrdersByUserId"
                    column="id"
                    ofType="com.hnucm.springboot.demo.pojo.Order">
        </collection>
    </resultMap>

    <select id="findAllUser" resultMap="orderandUser">
        select * from user;
    </select>

    <select id="findUserByid" resultMap="orderandUser"
            parameterType="Integer">
        select  * from user where id = #{id}
    </select>

    <insert id="addUser" parameterType="com.hnucm.springboot.demo.pojo.User">
        insert  into user (name,age) values (#{name},#{age})
    </insert>

    <update id="updateUser" parameterType="com.hnucm.springboot.demo.pojo.User">
         update user set name = #{name},age= #{age} where id= #{id}
    </update>
    <delete id="deleteUserByid" parameterType="Integer">
        delete from user where id = #{id}
    </delete>
</mapper>

```



```xml
<?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE mapper PUBLIC "-//mybatis.org//DTD Mapper 3.0//EN" "http://mybatis.org/dtd/mybatis-3-mapper.dtd">
<mapper namespace="com.hnucm.springboot.demo.dao.OrderMapper">
    <select id="findOrdersByUserId"
            resultType="com.hnucm.springboot.demo.pojo.Order"
            parameterType="Integer">
        select * from orders where userid=#{id}
    </select>

</mapper>
```





### Dao

```java
@Mapper
public interface OrderMapper {
    List<Order> findOrdersByUserId(int id);
}
```





```java
@Data
public class User {
    private int id;
    private int age;
    private String name;
    private List<Order> orderList;
}
```









## 多对多级联查询



>应用场景举例：用户与商品之间的关系为多对多， 一个订单可以有多种商品，使用一个中间表（订单记录表）就可以将多对多级联转换成两个一对多的关系
>

### Mapper

```xml
<?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE mapper PUBLIC "-//mybatis.org//DTD Mapper 3.0//EN" "http://mybatis.org/dtd/mybatis-3-mapper.dtd">
<mapper namespace="com.hnucm.springboot.demo.dao.OrderMapper">
    <select id="findOrdersByUserId"
            resultType="com.hnucm.springboot.demo.pojo.Order"
            parameterType="Integer">
        select * from orders where userid=#{id}
    </select>
    <resultMap id="orderAndProduct" type="com.hnucm.springboot.demo.pojo.Order">
        <id property="id" column="id"></id>
        <result property="orderinfo" column="orderinfo"/>
        <result property="userid" column="userid"/>
        <collection property="products" ofType="com.hnucm.springboot.demo.pojo.Product">
            <id property="id" column="pid"></id>
            <result property="name" column="name"/>
            <result property="price" column="price"/>
        </collection>
    </resultMap>
    <select id="findAllOrdersAndProduct" resultMap="orderAndProduct">
        select orders.* ,product.id as pid,product.name,product.price from
        orders,product,order_product where orders.id = order_product.order_id
        and product.id = order_product.product_id
    </select>
</mapper>

```



```java
@Mapper
public interface OrderMapper {
    List<Order> findOrdersByUserId(int id);
    List<Order> findAllOrdersAndProduct();
}
```





```java
@Data
public class Order {
    private int id;
    private int userid;
    private String orderinfo;
    // 多对多中的另一个一对多
    private List<Product> products;
}
```





### 根据条件查询

```xml
<?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE mapper PUBLIC "-//mybatis.org//DTD Mapper 3.0//EN" "http://mybatis.org/dtd/mybatis-3-mapper.dtd">
<mapper namespace="com.hnucm.springboot.demo.dao.OrderMapper">
    <select id="findOrdersByUserId"
            resultType="com.hnucm.springboot.demo.pojo.Order"
            parameterType="Integer">
        select * from orders where userid=#{id}
    </select>
    <resultMap id="orderAndProduct" type="com.hnucm.springboot.demo.pojo.Order">
        <id property="id" column="id"></id>
        <result property="orderinfo" column="orderinfo"/>
        <result property="userid" column="userid"/>
        <collection property="products" ofType="com.hnucm.springboot.demo.pojo.Product">
            <id property="id" column="pid"></id>
            <result property="name" column="name"/>
            <result property="price" column="price"/>
        </collection>
    </resultMap>
    <select id="findAllOrdersAndProduct" resultMap="orderAndProduct">
        select orders.* ,product.id as pid,product.name,product.price from
        orders,product,order_product where orders.id = order_product.order_id
        and product.id = order_product.product_id
    </select>
    <select id="findAllOrdersAndProductById" resultMap="orderAndProduct" parameterType="Integer">
        select orders.* ,product.id as pid,product.name,product.price from
        orders,product,order_product where orders.id = order_product.order_id
        and product.id = order_product.product_id and orders.id = #{id}
    </select>
    <select id="findAllOrdersAndProductByUserId" resultMap="orderAndProduct" parameterType="Integer">
        select orders.* ,product.id as pid,product.name,product.price from
        orders,product,order_product where orders.id = order_product.order_id
        and product.id = order_product.product_id and orders.userid = #{userid}
    </select>
</mapper>
```



```java
@Mapper
public interface OrderMapper {
    List<Order> findOrdersByUserId(int id);
    List<Order> findAllOrdersAndProduct();
    List<Order> findAllOrdersAndProductById( int id);
    List<Order> findAllOrdersAndProductByUserId( int userid);
}
```





### 根据Product查询

```xml
<?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE mapper PUBLIC "-//mybatis.org//DTD Mapper 3.0//EN" "http://mybatis.org/dtd/mybatis-3-mapper.dtd">
<mapper namespace="com.hnucm.springboot.demo.dao.ProductMapper">

    <resultMap id="productAndOrders" type="com.hnucm.springboot.demo.pojo.Product">
        <id property="id" column="id"></id>
        <result property="name" column="name"></result>
        <result property="price" column="price"></result>
        <collection property="orders" ofType="com.hnucm.springboot.demo.pojo.Order"  >
            <id property="id" column="id"></id>
            <result property="orderinfo" column="orderinfo"></result>
        </collection>
    </resultMap>
    <select id="findAllProductAndOrders"   resultMap="productAndOrders">
     SELECT product.*,orders.id,orders.orderinfo FROM orders,product,order_product WHERE orders.id = order_product.order_id AND order_product.product_id = product.id;
    </select>
</mapper>
```
