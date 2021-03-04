# IO流

## 文件类File

File类用于封装系统的文件和目录信息

创建对象

```
new File(String pathName)
new File(String parent,String child)//parent父抽象路径名，child：子路径名
```

获取文件信息

```java
String getName()//获取文件名
String getParent()//获取父路径字符串
String getPath()//获取文件的相对路径字符串
String getAbsolutePath()//获取文件的绝对路径
boolean exists()//判断文件或文件夹是否存在
boolean isFile()//判断是否是文件类型
boolean isDirectory()//判断是否是文件夹类型
boolean delete()//删除文件或文件夹，删除成功返回true（如果是目录，目录必须为空）
boolean mkdir()//创建文件夹，只能创建单层目录，创建成功返回true
boolean mkdirs()//创建文件夹，可创建多层目录，创建成功返回true
boolean setReadOnly()//设置文件或文件夹只读权限
long length()//获取文件长度
long lastModified()//获取文件的最后修改时间
String[] list()//获取文件夹中的文件和子文件夹的名称放到数组中
```

样例

```java
import java.io.File;

public class Main {
    public static void main(String[] args) throws InterruptedException {
        String DirectoryPath="D:\\我的文件";
        String newDirectory=DirectoryPath+"\\test";
        File file=new File(DirectoryPath);
        File newFile=new File(newDirectory);
        System.out.println(file.getParent());
        System.out.println(file.getPath());
        System.out.println(file.getAbsolutePath());
        System.out.println(file.exists());
        System.out.println(file.isFile());
        System.out.println(file.isDirectory());
        boolean flag=newFile.mkdir();
        if(flag) System.out.println("文件夹创建成功");
        Thread.sleep(2000);
        flag=newFile.delete();
        if (flag) System.out.println("文件夹删除成功");
        String[] lists=file.list();
        System.out.println("子文件名");
        for (String listName:lists){
            System.out.println(listName);
        }
        System.out.println(file.lastModified());

    }
}

```

## 字节输入输出流

### 字节输入流抽象类InputStream

定义了数据流读取和写入的基本方法

```java
int available()//可以读取的有效字节数量
int read()//读取一个字节，如果已经到末尾返回-1
int read(byte[] bytes)//读取长度最长为byte的长度的字节数据，返回读取的字节长度，到末尾返回-1
void reset()//重新定位到最后一个mark的位置
void mark(int readlimit)//做标记位置，当调用reset()方法时将返回到该位置，从标记位置开始，到再读入readlimit个字符为止，这个标记都维持有效
boolean markSupported()//测试当前流是否支持mark和reset方法，有一个不支持返回false
long skip(long n)//跳过并丢弃当前输入流的n个数据
```

样例

```java
import java.io.File;
import java.io.IOException;
import java.io.InputStream;

public class Main {
    public static void main(String[] args) throws IOException {
        InputStream in=System.in;
        byte[] bytes=new byte[1024];
        while ((in.read(bytes))!=-1){
            System.out.println(new String(bytes).trim());
        }
        in.close();
    }
}

```

### 字节输出流抽象类OutputStream

```java
void write(byte[] b)//将b中的数据写入当前流
void write(bye[] b,int off,in len)//将b中从off开始的len个字节数据写入当前流
void write(int b)//写入一个byte数据到当前流
void flush()//刷新缓存
```

样例

```java
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;

public class Main {
    public static void main(String[] args) throws IOException {
        InputStream in=System.in;
        OutputStream out=System.out;
        byte[] bytes=new byte[1024];
        while ((in.read(bytes))!=-1){
            out.write(bytes);

        }
        in.close();
    }
}

```

### 文件字节输入流

可以从指定文件读取数据

```java
new FileInputStream(File file)
new FileInputStream(String filepath)
```

### 文件字节输出流

```java
new FileOutputStream(File file)
new FileOutputStream(String filepath)
```

## 字符输入输出流

字节流以字节为单位传送数据，可以使任何类型的数据，例如文本、音频、视频、图片等。字符流以字符为单位传送数据，只能传送文本类型的数据。使用字符输入输出流的好处是，当读取中文时不会出现乱码问题，而使用字节输入输出流时，却不能保证这一点。

### 字符输入流抽象类Reader

```java
boolean ready()//判断数据流是否准备好
int read()//读入一个字符
int read(char[] c)
int read(char[] c,int off,int len)
void reset()
void mark(int readLimit)
boolean markSupported()
long skip(long n)
```

### 字符输出流抽象类Writer

```java
void write(char[] c)
void write(char[] c,int off,int len)
void write(int c)
void write(String str)
void write(String str,int off,int len)
void flush()
```

### 文件字符输入流FileReader

### 文件字符输出流FileWriter





