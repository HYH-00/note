## Docker

### 入门教程

启动容器命令

```bash
docker run -d -p 80:80 docker/getting-started
-d	以分离模式运行容器（在后台）
-p 80:80	将主机的80端口映射到容器中的80端口
docker/getting-started	要使用的图像
```



#### 获取当前所有镜像

```bash
docker image ls
# 或者
docker images
```

#### 拉取镜像

```bash
# 官方镜像
docker image pull 镜像名称 
# 或简写为 
docker pull 镜像名称
# 比如
docker pull ubuntu
docker pull ubuntu:16.04

# 个人镜像
docker pull 仓库名称/镜像名称
docker pull xunmi/django

# 第三方仓库拉取
docker pull 第三方仓库地址/仓库名称/镜像名称
docker pull hub.c.163.com/library/mysql:latest
(默认仓库名为library,所有从官方获取镜像相当于`sudo docker image pull library/镜像名称`)

```

#### 删除镜像

```bash
docker image rm 镜像名或镜像ID 或 docker rmi 镜像名或镜像ID
# 删除容器
docker image rm hello-world
# 删除镜像
docker rmi 9e64176cd8a2
# 删除镜像的前提是没有使用这个镜像的容器
```

#### 加载镜像

```bash
docker run [可选参数] 镜像名 [向启动容器中传入的命令]
```

-i	表示以《交互模式》运行容器。
-d	会创建一个守护式容器在后台运行(这样创建容器后不会自动登录容器)。
-t	表示容器启动后会进入其命令行。加入这两个参数后，容器创建就能登录进去。即分配一个伪终端。
–name	为创建的容器命名。(默认会随机给名字,不支持中文字符!!!)
-v	表示目录映射关系，即宿主机目录:容器中目录。注意:最好做目录映射，在宿主机上做修改，然后共享到容器上。
-p	表示端口映射，即宿主机端口:容器中端口。 比如 -p 8080:80 就是将容器中的80端口,映射到主机中的8080端口
–network=host	表示将主机的网络环境映射到容器中，使容器的网络与主机相同。每个 Docker 容器都有自己的网络连接空间连接到虚拟 LAN。使用此命令则会让容器和主机共享一个网络空间。

#### 查看容器

```bash
# 查看当前所有正在运行的容器
docker ps
# 查看当前所有的容器
docker ps -a
# 使用过滤器(除了name外,常用的还可以指定id:id= 、所有停止的容器:status=exited,正在运行的容器:status=running 等)
docker ps -f name=指定的名字
# 显示2个上次创建的容器(2可以改变)
docker ps -n 2
# 显示最新创建的容器（包括所有状态）
docker ps -l
# 仅显示ip
docker ps -q
 # 显示容器大小
docker ps -s
```

#### 启动和关闭容器

```bash
# 停止容器
docker container stop 容器名或容器id
# 或可简写为
docker stop 容器名或容器id

# 强制关闭容器
docker container kill 容器名或容器id
# 或可简写为
docker kill 容器名或容器id

# 启动容器
docker container start 容器名或容器id
# 或可简写为
docker start 容器名或容器id
```

#### Dockerfile

Dockerfile是用来定制化构建镜像的文件

```bash
FROM golang
FROM bitnami/kafka
RUN echo '这是一个本地构建的nginx镜像' > /usr/share/nginx/html/index.html
```

##### 使用Dockerfile构建镜像

```bash
docker build -t name:tag .
```

由于 docker 的运行模式是 C/S。我们本机是 C，docker 引擎是 S。实际的构建过程是在 docker 引擎下完成的，所以这个时候无法用到我们本机的文件。这就需要把我们本机的指定目录下的文件一起打包提供给 docker 引擎使用。

如果未说明最后一个参数，那么默认上下文路径就是 Dockerfile 所在的位置。