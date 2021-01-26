# SpringBoot

[TOC]

## SpringBoot概述

`SpringBoot `是由 `Pivotal` 团队提供的全新框架。Spring Boot 是所有基于 Spring Framework 5.0 开发的项目的起点。Spring Boot 的设计是为了让你尽可能快的跑起来 Spring 应用程序并且尽可能减少你的配置文件。

**设计目的：** 用来简化新 Spring 应用的初始搭建以及开发过程。

从最根本上来讲，Spring Boot 就是一些库的集合，它能够被任意项目的构建系统所使用。它使用 “习惯优于配置” （项目中存在大量的配置，此外还内置一个习惯性的配置）的理念让你的项目快速运行起来。 spring boot 其实不是什么新的框架，它默认配置了很多框架的使用方式，就像 maven 整合了所有的 jar 包，spring boot 整合了所有的框架，总结一下及几点：

（1）为所有 Spring 开发提供一个更快更广泛的入门体验。

（2）零配置。无冗余代码生成和XML 强制配置，遵循“约定大于配置” 。

（3）集成了大量常用的第三方库的配置， Spring Boot 应用为这些第三方库提供了几乎可以零配置的开箱即用的能力。

（4）提供一系列大型项目常用的非功能性特征，如嵌入式服务器、安全性、度量、运行状况检查、外部化配置等。

（5）Spring Boot 不是Spring 的替代者，Spring 框架是通过 IOC 机制来管理 Bean 的。Spring Boot 依赖 Spring 框架来管理对象的依赖。Spring Boot 并不是Spring 的精简版本，而是为使用 Spring 做好各种产品级准备



## SpringBoot的创建

<img src="https://i.loli.net/2020/12/19/SxRNfuJpcU86YVr.png" alt="image-20201219102615555" style="zoom: 33%;" />

<img src="https://i.loli.net/2020/12/19/BxFWJwaHPgQj98s.png" alt="image-20201219102709740" style="zoom:33%;" />

<img src="https://i.loli.net/2020/12/19/tyCO3cGTRB4965M.png" alt="image-20201219103107374" style="zoom:33%;" />

<img src="https://i.loli.net/2020/12/19/ADFzwHU6ObcjsLP.png" alt="image-20201219103123585" style="zoom:33%;" />

**Spring Boot DevTools：热部署**

**Lombok能以简单的注解形式来简化java代码，提高开发人员的开发效率**

**Spring Configuration Processor：spring默认使用yml中的配置，选中即使用传统的xml或properties配置**



## SpringBoot的热部署

`pom.xml`中添加

```xml
<!--devtools热部署-->
 <dependency>
 <groupId>org.springframework.boot</groupId>
 <artifactId>spring-boot-devtools</artifactId>
 <optional>true</optional>
 <scope>true</scope>
 </dependency>
 
 
 
 <plugin>
 <groupId>org.springframework.boot</groupId>
 <artifactId>spring-boot-maven-plugin</artifactId>
 <configuration>
 <fork>true</fork>
 </configuration>
 </plugin>
```



<img src="https://i.loli.net/2020/12/19/9EGl4XUzkbtLioN.png" alt="image-20201219104128795" style="zoom:33%;" />

ctrl + shift + alt + / ,选择Registry,勾上 Compiler autoMake allow when app running

<img src="https://i.loli.net/2020/12/19/E1fvHVInuLTPcr5.png" alt="image-20201219104220068" style="zoom: 50%;" />

<img src="https://i.loli.net/2020/12/19/k7Vz6uJe19hFIDR.png" alt="image-20201219104250209" style="zoom:33%;" />

<img src="https://i.loli.net/2020/12/19/IKTGf75g2WniALJ.png" alt="image-20201219104325344" style="zoom:50%;" />

<img src="https://i.loli.net/2020/12/19/amCvO487HkFiK6j.png" alt="image-20201219104407728" style="zoom:33%;" />





## SpringBoot默认配置文件

### 端口服务配置

```yml
#端口，项目上下文根
server:
	port: 8088
	servlet:
		context-path: /springboot
spring:
	datasource:
		username: root
		password: 123456
		url: jdbc:mysql://localhost:3306/mybatis?useUnicode=true&characterEncoding=utf-8&useSSL=true&serverTimezone=UTC
		driver-class-name: com.mysql.cj.jdbc.Driver
mybatis:
	mapper-locations: classpath:mapper/*.xml
	type-aliases-package: com.hnucm.springboot.pojo
#sql日志显示在控制台
logging:
	level:
		com:
			hnucm:
				springboot: debug
```



## SpringBoot依赖包

```xml
<dependency>
	<groupId>org.mybatis.spring.boot</groupId>
	<artifactId>mybatis-spring-boot-starter</artifactId>
	<version>2.1.3</version>
</dependency>
<dependency>
	<groupId>mysql</groupId>
	<artifactId>mysql-connector-java</artifactId>
	<version>8.0.20</version>
</dependency>
```



## 工程目录

<img src="https://i.loli.net/2020/12/19/CA4FEp5kJxSisa8.png" alt="image-20201219110243451" style="zoom:33%;" />



## 返回数据封装类

```java
package com.hnucm.springboot.demo.pojo;

import java.util.HashMap;
import java.util.Map;

/**
 * 返回数据封装类
 */
public class Result extends HashMap<String, Object> {
    private static final long serialVersionUID = 1L;

    public Result() {
        put("code", 0);
        put("msg", "success");
    }

    public static Result error() {
        return error(500, "未知异常，请联系管理员");
    }

    public static Result error(String msg) {
        return error(500, msg);
    }

    public static Result error(int code, String msg) {
        Result r = new Result();
        r.put("code", code);
        r.put("msg", msg);
        return r;
    }

    public static Result ok(String msg) {
        Result r = new Result();
        r.put("msg", msg);
        return r;
    }

    public static Result ok(Map<String, Object> map) {
        Result r = new Result();
        r.putAll(map);
        return r;
    }

    public static Result ok() {
        return new Result();
    }

    public Result put(String key, Object value) {
        super.put(key, value);
        return this;
    }
}
```



## 统一异常处理

```java
package com.hnucm.springboot.demo;

import com.hnucm.springboot.demo.pojo.Result;
import org.springframework.web.bind.annotation.ControllerAdvice;
import org.springframework.web.bind.annotation.ExceptionHandler;
import org.springframework.web.bind.annotation.ResponseBody;

import java.sql.SQLException;

@ControllerAdvice
public class MyControllerAdvice {


    @ResponseBody
    @ExceptionHandler(value = SQLException.class)
    public Result sqlHandler(Exception ex) {
        return Result.error(501,ex.getMessage());
    }


    /**
     * 全局异常捕捉处理
     * @param ex
     * @return
     */
    @ResponseBody
    @ExceptionHandler(value = Exception.class)
    public Result errorHandler(Exception ex) {
        return Result.error(500,ex.getMessage());
    }

}
```



## 自定义异常

```java
package com.hnucm.springboot.util;
/**
 * 自定义异常
 *
 */
public class MyException extends RuntimeException {
    private static final long serialVersionUID = 1L;
    private String msg;
    private int code = 500;
    public MyException(String msg) {
        super(msg);
        this.msg = msg;
    }
    public MyException(String msg, Throwable e) {
        super(msg, e);
        this.msg = msg;
    }
    public MyException(String msg, int code) {
        super(msg);
        this.msg = msg;
        this.code = code;
    }
    public MyException(String msg, int code, Throwable e)
    {
        super(msg, e);
        this.msg = msg;
        this.code = code;
    }
    public String getMsg() {
        return msg;
    }
    public void setMsg(String msg) {
        this.msg = msg;
    }
    public int getCode() {
        return code;
    }
    public void setCode(int code) {
        this.code = code;
    }
}
```

