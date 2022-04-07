```
pip config set global.index-url https://pypi.tuna.tsinghua.edu.cn/simple

conda env create -f environment.yml

pip config unset global.index-url

conda activate gluon

# python -m pip install --upgrade pip --target=D:\Users\MECHREVO\miniconda3\envs/gluon/Lib/site-packages

#pip install mxnet
#pip install d2lzh==0.8.11
#pip install jupyter==1.0.0
#pip install matplotlib==2.2.2
#pip install pandas==0.23.4


jupyter notebook

http://localhost:8888

set MXNET_GLUON_REPO=https://apache-mxnet.s3.cn-north-1.amazonaws.com.cn/jupyter notebook
```

## 创建环境

```
conda create -n {name} {指定版本}
```



