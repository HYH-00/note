# TCP/IP协议

## InetAddress

封装一个IP地址，并提供了一系列与IP地址相关的方法

常用的有

| 返回值              | 方法                      | 描述                             |
| ------------------- | ------------------------- | -------------------------------- |
| static  InetAddress | getByname(String host)    | 在给定主机名的情况下确定主机地址 |
| static  InetAddress | getByAddress(byte[] addr) | 在给定主机地址的情况下确定主机名 |
| satic  InetAddress  | getLocalHost()            | 获取本地主机名                   |
| String              | getHostName()             | 获取此IP的主机名                 |
| String              | getHostAddress()          | 获取此IP的IP地址（文本格式）     |

```java
import java.net.InetAddress;
import java.net.UnknownHostException;

public class Main {
    public static void main(String[] args) throws UnknownHostException {
        InetAddress inetAddress=InetAddress.getLocalHost();
        System.out.println(inetAddress);
        System.out.println(inetAddress.getHostName());
        System.out.println(inetAddress.getAddress());

        String hostName=inetAddress.getHostName();
        //不存在的主机名会报错
        System.out.println(InetAddress.getByName(hostName));

        byte[] address=inetAddress.getAddress();
        //不存在的地址字符数组会报错
        System.out.println(InetAddress.getByAddress(address));
    }
}

```

## UDP

无连接的协议，速度快，但数据完整性不能保证

可以通过重传控制，拥塞控制使UDP可靠

通常用于对数据完整性不那么依赖的场合，如音频、视频和普通数据的传输

## TCP

面向连接的协议，速度没UDP快，但是数据完整性有保证

连接需要三次握手，断开连接需要四次挥手

PS：四次挥手客户端需要等待2MSL时间，确保由于网络堵塞等原因迟到且客户端重发的消息在本次连接中作废掉，防止进入下一个连接中

## UDP通信

**DatagramPacket：数据包**

相当于一个集装箱，用于封装UDP发送和接受的数据

接收端：不需要指定端口，只需要提供一个byte数组和长度即可接收数据

```java
DatagramPacket(byte[] buf，int length)
```

发送端：需要指定数据包的目的主机和目的端口

```java
DatagramPacket(byte[] buf，int length，InetAddress address，int port)
```

常用方法

```java
getAddress()
getPort()
getData()
getLength()
```

**DatagramSocket：数据报套接字**

相当于一个码头，来接收和发送集装箱

发送端：不需要指定特定端口

```java
DatagramSocket()//构造数据报套接字，绑定到本机任意一个可用端口
```

接收端：需要指定端口，知道货物从码头那个位置运输过来

```java
DatagramSocket(int port)
```

常用方法

```java
receive(DatagramPacket p)//从此套接字接收数据，数据保存到p中
send(DatagramPacket p)//发送此套接字的数据
```

样例

```java
//Main
public class Main {
    public static void main(String[] args) {
        Thread client=new Thread(new Client());
        Thread server=new Thread(new Server());
        server.start();
        client.start();
    }
}
//Client
import java.io.IOException;
import java.net.*;
import java.nio.charset.StandardCharsets;

public class Client implements Runnable{
    @Override
    public void run() {
        try {
            byte[] s="我是客户端，呼叫服务端".getBytes(StandardCharsets.UTF_8);
            DatagramPacket datagramPacket=new DatagramPacket(s,s.length, InetAddress.getByName("127.0.0.1"),9999);
            DatagramSocket datagramSocket=new DatagramSocket();
            datagramSocket.send(datagramPacket);
            datagramSocket.close();
        } catch (UnknownHostException | SocketException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
//Server
import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.SocketException;

public class Server implements Runnable{
    @Override
    public void run() {
        try {
            byte[] s=new byte[1024];
            DatagramPacket datagramPacket=new DatagramPacket(s,s.length);
            DatagramSocket datagramSocket=new DatagramSocket(9999);
            System.out.println("服务端接收————————————————————————--");
            datagramSocket.receive(datagramPacket);
            System.out.println("IP:"+datagramPacket.getAddress()+"      Port:"+datagramPacket.getPort());
            System.out.println(new String(datagramPacket.getData()));
            datagramSocket.close();
        } catch (SocketException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}

```

## TCP通信

java中提供了两个类来建立连接

服务端：ServerSocket

```java
accept()//侦听此套接字的连接，返回一个套接字，即连接上来的客户端（阻塞线程）
getInetAddress()//返回此服务器套接字的监听的地址
```

客户端：Socket

```java
//Construction
Socket(String host,int port)//创建一个套接字并将其绑定到指定主机的指定端口上
Socket(InetAddress address,int port)//绑定到指定IP地址的指定端口号
//Method
int getPort()//获取套接字连接的端口号
InetAddress getLocalAddress()//获取套接字绑定的IP地址
InputStream getInputStream()
OutputStream getOutputStream()
```

样例

```java
//Main
public class Main {
    public static void main(String[] args) {
        Thread client=new Thread(new Client());
        Thread server=new Thread(new Server());
        server.start();
        client.start();
    }
}
//Client
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.*;
import java.nio.charset.StandardCharsets;

public class Client implements Runnable{
    @Override
    public void run() {
        try {
            Socket socket=new Socket("127.0.0.1",9999);
            InputStream in=socket.getInputStream();
            OutputStream out=socket.getOutputStream();
            byte[] s=new byte[1024];
            in.read(s);
            System.out.println(new String(s));
            out.write("Hello,我是客户端".getBytes(StandardCharsets.UTF_8));

            in.close();
            out.close();
            socket.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
//Server
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.*;
import java.nio.charset.StandardCharsets;

public class Server implements Runnable{
    @Override
    public void run() {
        try {
            ServerSocket serverSocket=new ServerSocket(9999);
            Socket socket=serverSocket.accept();
            InputStream in=socket.getInputStream();
            OutputStream out=socket.getOutputStream();
            out.write("你已经连接上了服务器".getBytes(StandardCharsets.UTF_8));
            byte[] s=new byte[1024];
            in.read(s);
            System.out.println(new String(s));

            in.close();
            out.close();
            socket.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}

```

