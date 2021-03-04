# Spring全家桶——interview

## Spring

Spring是一个开源容器框架，可以接管web层，业务层，dao层，持久层的组件，并且可以配置各种bean,和维护bean与bean之间的关系。其核心就是控制反转(IOC),和面向切面(AOP),简单的说就是一个分层的轻量级开源框架

### 循环依赖

实例化->填充属性->初始值

#### 三级缓存

- 一级缓存：第一级缓存，存放可用的`成品Bean`。
- 二级缓存：存放`半成品的Bean`，`半成品的Bean`是已创建对象，但是未注入属性和初始化。用以解决循环依赖
- 三级缓存：存的是`Bean工厂对象`，用来生成`半成品的Bean`并放入到二级缓存中。用以解决循环依赖

singletonObjects：单例对象的cache

earlySingletonObjects ：提前暴光的单例对象的Cache

singletonFactories ： 单例对象工厂的cache



Spring首先从一级缓存singletonObjects中获取。如果获取不到，并且对象正在创建中，就再从二级缓存earlySingletonObjects中获取。如果还是获取不到且允许singletonFactories通过getObject()获取，就从三级缓存singletonFactory.getObject()(三级缓存)获取



为什么要包装一层`ObjectFactory`对象？

如果创建的`Bean`有对应的`代理`，那其他对象注入时，注入的应该是对应的`代理对象`；但是`Spring`无法提前知道这个对象是不是有`循环依赖`的情况，而`正常情况`下（没有`循环依赖`情况），`Spring`都是在创建好`完成品Bean`之后才创建对应的`代理`。这时候`Spring`有两个选择：

1. 不管有没有`循环依赖`，都`提前`创建好`代理对象`，并将`代理对象`放入缓存，出现`循环依赖`时，其他对象直接就可以取到代理对象并注入。
2. 不提前创建好代理对象，在出现`循环依赖`被其他对象注入时，才实时生成`代理对象`。这样在没有`循环依赖`的情况下，`Bean`就可以按着`Spring设计原则`的步骤来创建。

`Spring`选择了第二种方式，那怎么做到提前曝光对象而又不生成代理呢？
Spring就是在对象外面包一层`ObjectFactory`，提前曝光的是`ObjectFactory`对象，在被注入时才在`ObjectFactory.getObject`方式内实时生成代理对象，并将生成好的代理对象放入到第二级缓存

### BeanFactory和FactoryBean

BeanFactory是个Factory，也就是IOC容器或对象工厂，FactoryBean是个Bean。在Spring中，所有的Bean都是由BeanFactory(也就是IOC容器)来进行管理的。但对FactoryBean而言，这个Bean不是简单的Bean，而是一个能生产或者修饰对象生成的工厂Bean,它的实现与设计模式中的工厂模式和修饰器模式类似

`BeanFactory只是个接口，并不是IOC容器的具体实现`

BeanFactory是个bean 工厂，是一个工厂类(接口)， 它负责生产和管理bean的一个工厂
是ioc 容器最底层的接口，是个ioc容器，是spring用来管理和装配普通bean的ioc容器（这些bean成为普通bean）。

FactoryBean是个bean，在IOC容器的基础上给Bean的实现加上了一个简单工厂模式和装饰模式，是一个可以生产对象和装饰对象的工厂bean，由spring管理后，生产的对象是由getObject()方法决定的（从容器中获取到的对象不是
“ FactoryBeanTest ” 对象）。

### IOC

DI(依赖注入)：在容器创建对象后，处理对象的依赖关系。

使用ConcurrentHashMap存储对象

依赖注入spring的注入方式

- setter
- 静态工厂
- 构造方法
- 基于注解

优点：

- 降低耦合度，子组件可以不依赖父组件
- 替换实现比较方便，直接注入就可以

### AOP

jdk动态代理

### @Resource和@Autowired

@Autowired是Spring的

@Resource是J2EE的

@Autowired默认情况下必须要求依赖对象必须存在，如果要允许null值，可以设置它的required属性为false

@Autowired是安装类型装配的，如果需要按照名称装配可以使用Qualifier

@Resource有两个属性是比较重要的，分是name和type，Spring将@Resource注解的name属性解析为bean的名字，而type属性则解析为bean的类型。所以如果使用name属性，则使用byName的自动注入策略，而使用type属性时则使用byType自动注入策略。如果既不指定name也不指定type属性，这时将通过反射机制使用byName自动注入策略

### Spring Bean的生命周期

四个阶段和多个拓展点

大致为：创建实例->注入属性->初始化>摧毁

详细：

- **实例化**
- **注入属性**
- 注入Aware接口（将相关的xxxAware实例注入给bean）
- BeanPostProcessor的before方法（可以在InitialzationBean前执行操作）
- **initialzationBean**
- BeanPostProcessor的after方法（可以在InitialzationBean前执行操作）
- 使用Bean
- DisposableBean接口（调用destroy）
- **销毁bean**

### 事务

Spring支持声明式事务和编程式事务

### 设计模式

- 简单工厂模式：BeanFactory就是简单工厂模式的体现
- 工厂方法模式：应用程序自己的工厂对象交给Spring管理,那么Spring管理的就不是普通的bean,而是工厂Bean
- 单例模式：保证一个类仅有一个实例，并提供一个访问它的全局访问点
- 适配器模式：AOP
- 代理模式：AOP
- 观察者模式：事件
- 策略模式
- 模板方法模式

IOC使用的设计模式

- 工厂方法模式
- 单例模式
- 策略模式

## SpringMVC

SpringMVC是一种web层mvc框架，用于替代servlet（处理|响应请求，获取表单参数，表单校验等。SpringMVC是一个MVC的开源框架

### 处理请求流程

->前端控制器DispatcherServlet ->处理器映射组件 HandlerMapping

DispatcherServlet——>HandlerAdapter，HandlerAdapter将会把处理器包装为适配器，从而支持多种类型的处理器，即适配器设计模式的应用，从而很容易支持很多类型的处理器；

HandlerAdapter——>处理器功能处理方法的调用，HandlerAdapter将会根据适配的结果调用真正的处理器的功能处理方法，完成功能处理；并返回一个ModelAndView对象（包含模型数据、逻辑视图名）；                                                                                                                                                                                                                                                                                                      ->DispatcherServlet 需要根据 ModelAndView 解析视图。返回相应的视图对象 View

->由 View 渲染视图，并将渲染结果返回给用户

## SpringBoot

Springboot是一个微服务框架，延续了spring框架的核心思想IOC和AOP，简化了应用的开发和部署。Spring Boot是为了简化Spring应用的创建、运行、调试、部署等而出现的，使用它可以做到专注于Spring应用的开发，而无需过多关注XML的配置。提供了一堆依赖打包，并已经按照使用习惯解决了依赖问题--->习惯大于约定

spring mvc < spring < springboot