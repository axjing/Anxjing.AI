<!--
 * @Author: Anxjing.AI
 * @Date: 2020-05-27 12:26:29
 * @LastEditTime: 2020-05-27 21:59:38
 * @LastEditors: Anajing.AI
 * @Description: 
 * @FilePath: \Anxjing.AI\JingNotebook\Anself\matlab常用函数.md
 * @THIS FILE IS PART OF Anxjing.AI PROJECT
 -->
# **MATLAB数字图像常用函数**

# MATLAB图像预处理
## 图像处理的基本操作
1. 读入并显示一幅图像

```matlab
clear               %清除所有的工作平台变量
close all            %关闭已打开的图形窗口
I=imread ('pout.tif');   %读取图像pout.tif(该图像是图像处理工具箱自带的图像)，
%存储在一个名为I的数组中
imshow(I)           %显示图像I
```

2. 检查内存中的图像
```matlab
  whos    %查看图像数据I是如何存储在内存中的。
```

3. 实现直方图均衡化
```matlab
  figure           %生成一个新的图形窗口，避免后面的图像覆盖前面图像的显示
imhist(I)         %创建描述图像I灰度分布的直方图
I2=histeq(I);      %将图像的灰度值扩展到整个灰度范围，从而提高图像数组I的对比度。
figure,imshow(I2)  %显示修改过的图像I2
figure,imhist(I2)    %显示拓展后的灰度值的分布情况
```
4. 保存图像
```matlab
  imwrite(I2,'pout.png');  %将图像I2以PNG图像文件格式保存到磁盘
```
5. 检查新生成文件的内容
```matlab
  imfinfo('pout2.png')    %观察保存的图像文件信息

```

### 图像处理的高级应用
主要对一幅灰度图像rice.tif进行一些较为高级的操作为例说明整个过程。
1. 读取和显示图像
```matlab
  clear               %清除所有的工作平台变量
close all             %关闭已打开的图形窗口
I=imread('rice.png');   %读取图像rice.png (该图像是图像处理工具箱自带的图像)
imshow(I)           %显示图像
```
2. 估计图像背景
```matlab
  background=imopen(I,strel('disk',15));  %对图像I进行形态学开操作，删除那些不完全包括
%在半径为15的圆盘中的对象，实现对背景亮度的估计
  figure,imshow(background)
  figure,surf(double(background(1:8:end,1:8:end))),zlim([0 255]);  %以表面形式显示背景
```
3. 从原始图像中减去背景图像
```matlab
  I2=imsubtract(I,background);   %将背景图像background从原始图像I中减去
figure,imshow(I2)
```
4. 调节图像对比度
```matlab
  I3=imadjust(I2,stretchlim(I2),[0 1]);  %调节图像的对比度
figure,imshow(I3);
```
5. 使用阈值操作将图像转换为二进制图像
```matlab
  level=graythresh(I3);
bw=im2bw(I3,level);
figure,imshow(bw)
```

6. 检查图像中的对象个数
```matlab
  [labeled,numObjects]=bwlabel(bw,4);  %确定图像中的米粒个数
numObjects
   101
```
7. 检查标记矩阵
```matlab
  grain=imcrop(labeled)  %选择并显示已标记的对象和部分背景内的像素
  RGB_label=label2rgb(labeled,@spring,'C','shuffle');  
%将标记矩阵显示为一副伪彩色的索引图像，在伪彩色的彩色图像中，
%标记矩阵中的每一个对象都将被映射为相关调色板中的不同颜色
imshow(RGB_label);
```
8.计算图像中对象的统计属性
```matlab
  graindata=regionprops(labeled,'basic')  
%测量图像或者区域的属性，并返回一个结构数组。当用于一个标记图像时，%它还为每一个标记分量创建一个结构元素。
  graindata(51).Area  %显示第51个元素的属性

  graindata(51).BoundingBox,graindata(51).Centroid  %寻找最近的边缘和中心

  allgrains=[graindata.Area];  %创建一个新的向量allgrains，其包含每个米粒的范围
  allgrains(51)  %查看第51个元素的范围

  max(allgrains)  %获取最大的米粒大小

  biggrain=find(allgrains==404)  %返回最大米粒的标记号

  mean(allgrains)  %获取米粒的平均大小

  hist(allgrains,20)  %绘制包含20个柱的直方图
```

# MATLAB图像处理工具
## 常用图像格式
图像格式：是存储图像采用的文件格式。不同的操作系统、不同的图像处理软件，所支持的图像格式都有可能不同。
在实际应用中经常会遇到的图像格式有：BMP、GIF、TIFF、PCX、JPEG、PSD、PCD、
WMF等。
*(1) BMP(Bitmap)文件
*(2)GIF文件
*(3)TIF文件
*(4)JPEG文件


## MATLAB图像类型
图像类型：是指数组数值与像素颜色之间定义的关系，它与图像格式概念有所不同。
在MATLAB图像处理工具箱中，有五种类型的图像：
1. 二进制图像
在一幅二进制图像中，每一个像素将取两个离散数值(0或1)中的一个，从本质上说，这两个数值分别代表状态“开”(on)或“关”(off)。
二进制图像仅使用unit8或双精度类型的数组来存储。
在图像处理工具箱中，任何返回一幅二进制图像的数组均使用unit8逻辑数组存储该图像，并且使用一个逻辑标志来指示unit8逻辑数组的数据范围。
若逻辑状态为“开”（on），数组范围为[0,1]；若为“关”（off），则数组范围为[0,255]。

2. 索引图像
索引图像：是一种把像素值直接作为RGB调色板下标的图像。
在MATLAB中，索引图像包含有一个数据矩阵X和一个颜色映射（调色板）矩阵map。数据矩阵：可以是unit8、unit16、双精度类型的；
颜色映射矩阵map：是一个m×3的数据矩阵，其中每个元素的值均为[0,1]之间的双精度浮点型数据，map矩阵的每一行分别表示红色、绿色和蓝色的颜色值。
索引图像可把像素值直接映射为调色板数值，每一个像素的颜色通过使用X的数值作为map的下标来获得，如值1指向矩阵map中的第一行，值2指向第二行，依此类推。
颜色映射通常与索引图像存储在一起，当装载图像时，MATLAB自动将颜色映射表与图像同时装载。
图像矩阵与颜色映射表之间的关系依赖于图像数据矩阵的类型。
如果图像数据矩阵是双精度类型，则数据1指向矩阵map中的第一行，数据值2将指向map中的第二行，依此类推；
如果图像矩阵是unit8或unit16类型时，将产生一个偏移，即数值0表示矩阵map中的第一行，数据值1将指向map中的第二行，依此类推。

3. 灰度图像
灰度图像通常由一个unit8、unit16、双精度类型的数组来描述，其实质是一个数据矩阵I，该矩阵中的数据均代表了在一定范围内的灰度级，每一个元素对应于图像的一个像素点，通常0代表黑色，1、255、65 535（针对不同存储类型）代表白色。

4. 多帧图像
多帧图像是一种包含多幅图像或帧的图像文件，又称为多页图像或图像序列。
在MATLAB中，它是一个四维数组，其中第四维用来指定帧的序号。
在一个多帧图像数组中，每一幅图像必须有相同的大小和颜色分量，每一幅图像还要使用相同的调色板。另外，图像处理工具箱中的许多函数（如：imshow）只能对多幅图像矩阵的前两维或三维进行操作，也可以对四维数组使用这些函数，但是必须单独处理每一帧。如果将一个数组传递给一个函数，并且数组的维数超过该函数设计的超作维数，那么得到的结果是不可预知的。

5. RGB图像
RGB图像又称为真彩色图像，它是利用R、G、B三个分量表示一个像素的颜色，R、G、B分别代表红、绿、篮3种不同的颜色，通过三基色可以合成出任意颜色。所以对一个尺寸为n×m的彩色图像来说，在MATLAB中则存储为一个n×m×3的多维数据数组，其中数组中的元素定义了图像中的每一个像素的红、绿、篮颜色值。图形文件格式把RGB图像存储为24位的图像，红、绿、篮分量分别占用8位。
MATLAB的RGB数组可以是双精度的浮点型、8位或16位无符号的整数类型。在一个双精度类型的RGB数组中，每一个颜色分量都是一个[0,1]范围内的数值。如：颜色分量为(0,0,0)的像素将显示为黑色；颜色分量为(1,1,1)的像素将显示为白色。每一个像素的三个颜色分量都存储在数组的第三维中。如：像素（10，5）的红、绿、篮颜色值分别保存在元素RGB(10,5,1)、RGB(10,5,2)、RGB(10,5,3)中。

例：创建一个简单的RGB图像，该图像包含某一范围内不中断的红、绿、篮颜色分量，另外，
针对每一个颜色分量各创建一幅图像来加以对比：
```matlab
RGB=reshape(ones(64,1)*reshape(jet(64),1,192),[64,64,3]);
R=RGB(:,:,1);
G=RGB(:,:,2);
B=RGB(:,:,3);
subplot(2,2,1);imshow(R);
subplot(2,2,2);imshow(G);
subplot(2,2,3);imshow(B);
subplot(2,2,4);imshow(RGB);
```

## MATLAB图像类型转换
1. 图像颜色浓淡处理（图像抖动）
```matlab
X=dither(RGB,map)  %通过抖动算法将真彩色图像RGB按指定的颜色（调色板）map转换
成索引色图像X
X=dither(RGB,map,Qm,Qe)  
%利用给定的参数Qm，Qe从真彩色图像RGB中产生索引色图像X。
%Qm表示沿每个颜色轴反转颜色图的量化（即对于补色各颜色轴）的位数，
%Qe表示颜色空间计算误差的量化误差。
              %如果Qe<Qm，则不进行抖动操作。Qm的默认值是5，Qe的默认值是8。
BW=dither(I)  %通过抖动算法将矩阵I中的灰度图像转换为二进制图像。
```
注意：
输入图像可以是双精度类型或8位无符号类型，其他参数必须是双精度类型。
如果输出的图像是二值图像或颜色种类少于256的索引图像时，为uint8类型，否则为doule型。

例：由RGB图像产生一个索引图像
使用索引图像chess.met的颜色图map，通过抖动map中的颜色，产生RGB图像autumn.tif的近似索引图像。
```matlab
load chess;
RGB=imread('autumn.tif');
subplot(1,2,1);imshow(RGB);
Y=dither(RGB,map)
subplot(1,2,2);imshow(Y,map);
```
2. 灰度图像转换为索引图像
```matlab
[X,map]=gray2ind(I,n)  %按指定的灰度级数n和颜色图map，将灰度图像I转换成索引色
%图像X，n的默认值为64。
例：将灰度图像pout.tif转化成索引图像X，颜色图分别为gray(128)和gray(16)。
I=imread('pout.tif');
[I1,map1]=gray2ind(I,128);
[I2,map2]=gray2ind(I,16);
subplot(1,3,1);imshow(I1,map1);
subplot(1,3,2);imshow(I2,map2);
subplot(1,3,3);imshow(I);
```
3. 索引图像转换为灰度图像
```matlab
I=ind2gray(X,map)  %将具有颜色图map的索引色图像X转换成灰度图像I，去掉了图像的
%色度和饱和度，仅保留了图像的亮度信息。
%输入图像可以是double或unit8类型。
例：将一幅索引图像trees.mat转换成灰度图像。
load trees
I=ind2gray(X,map);
subplot(1,2,1);imshow(X,map);
subplot(1,2,2);imshow(I);
```

4. RGB图像转换为灰度图像
```matlab
I=rgb2gray(RGB)        %将真彩色图像RGB转换成灰度图像I。
Newmap=rgb2gray(map)  %将颜色图map转换成灰度级颜色图。
```
注意：如果输入的是真彩色图像，则图像可以是8位无符号类型或双精度类型，输出图像I
与输入图像类型相同。
      如果输入的是颜色图，则输入和输出的图像均为双精度类型。
*例：将RGB图像flowers.tif转换为灰度图像。
```matlab
RGB=imread('flowers.tif');
figure(1);imshow(RGB)
figure(2);Y=rgb2gray(RGB);imshow(Y)
```
5. RGB图像转换为索引图像
```matlab
[X,map]=rgb2ind(RGB)   %直接将RGB图像转换为具有颜色图map的矩阵X.
[X,map]=rgb2ind(RGB,tol)  %用均匀量化的方法将RGB图像转换为索引图像X.
[X,map]=rgb2ind(RGB,n)  %使用最小方差量化的方法将RGB图像转换为索引图像，
%map中包括至少n个颜色。
X=rgb2ind(RGB,map)     %通过将RGB中的颜色与颜色图map中最相近的颜色匹配，
%将RGB图像转换为具有map颜色图的索引图像。
[…]=rgb2ind(…,dither_option)  
%通过dither_option参数来设置是否抖动。dither_option为dither表示使用抖动，以达到
%较好的颜色效果；缺省时为nodither，使用了新颜色图中最接近的颜色来画原图的颜色。

%*例：将RGB图像flowers.tif转换为索引图像。
RGB=imread('flowers.tif');
figure(1);imshow(RGB)
figure(2);Y=rgb2ind(RGB,128);imshow(Y)
```
6. 索引图像转换为RGB图像
```matlab
RGB=ind2rgb(X,map)  %将矩阵X及相应颜色图map转化成真彩图像RGB。
输入图像X可以是双精度类型或8位无符号类型，输出图像RGB为双精度类型。 
例：将索引图像wmandril.mat转换为RGB图像。
load wmandril;
figure(1);imshow(X,map);
I=ind2rgb(X,map);
figure(2);imshow(I)
```
7. 通过阈值化方法将图像转换为二值图像
im2bw函数：通过设置亮度阈值将真彩图像、索引图像及灰度图像转化成二值图像。在转换过程中，如果输入图像不是灰度图像，首先将其转换为灰度级图像，然后通过阈值化将灰度级图像转换成二值图像。输出二值图像在输入图像所有亮度小于给定值（level取值范围为[0,1]）像素点处均为0，其他均为1。其语法格式为：
```matlab
BW=im2bw(I,level)       %将灰度图像I转化为黑白二值图像。
BW=im2bw(X,map,level)  %将带有颜色图map的索引图像X转化为黑白二值图像。
BW=im2bw(RGB,level)   %将RGB图像转化为黑白二值图像。
```
注意：输入图像可以是双精度类型或8位无符号类型，输出图像为8位无符号类型。 

例：通过阈值化方法将索引图像trees.mat转换为二值图像，阈值为0.4。
```matlab
load trees;
BW=im2bw(X,map,0.4);
figure(1);imshow(X,map);
figure(2);imshow(BW)
```
8. 通过阈值化方法从灰度图像产生索引图像
```matlab
X=grayslice(I,n)  %将灰度图像I均匀量化为n个等级，然后转换为伪彩色图像X。
X=grayslice(I,v)  %按指定的阈值向量v（每一个元素都在0和1之间）对图像I的值域进行
```
划分，而后转换成索引图像X。
注意：输入图像I可以是双精度类型或8位无符号类型。
如果阈值数量小于256，则返回图像X的数据类型是8位无符号类型，X的值域为[0,n]
或[0,length(v)]；
否则，返回图像X为双精度类型，值域为[1,n+1]或[1,length(v)+1]。 
*例：将一幅灰度图像转换成索引图像。
```matlab
I=imread('alumgrns.tif');
figure(1);imshow(I);
X=grayslice(I,16);
figure(2);imshow(X,hot(16));
```

9. 将矩阵转换为灰度图像
```matlab
I=mat2gray(X,[xmin,xmax])  
%按指定的取值区间[xmin,xmax]将数据矩阵X转换为图像I,xmin对应灰度0（最暗即黑），%xmax对应灰度1（最亮即白）。如果不指定区间[min,max]时，MATLAB则自动将X阵中%最小设为xmin，最大设为xmax。
```

注意：输入X和输出图像I都是双精度类型。实际上，mat2gray函数与imshow函数功能类
似。Imshow函数也可用来使数据矩阵可视化。
*例：将图像滤波后产生的矩阵转换为灰度图像。
```matlab
I=imread('saturn.tif');
J=filter2(fspecial('sobel'),I);
K=mat2gray(J);
figure(1);imshow(I);
figure(2);imshow(K);
```

## 图像的显示
图像的显示过程：将图像从一组离散数据还原为一幅可见的图像的过程。
图像的显示是提高图像处理分析性能非常有用的一个手段，通过图像的显示，可以监视图像处理过程，并与处理分析交互地控制处理分析过程。
图像显示最重要的特性是图像的大小、光度分辨率、灰度线性、平坦能力和噪声特性等，这些显示特性将共同决定一个数字图像显示系统的质量及其在特定应用中的适用性等性能指标。
### 标准图像显示技术
Matlab显示图像的主要方法是调用image函数，该函数可创建一个句柄图形图像对象，并且包含设置该对象的各种属性的调用语法；此外，还提供了与image函数类似的imagesc函数，利用该函数，可以实现对输入图像数据的自动缩放。同时，还包含了一个附加的显示函数，即imshow函数，与image和imagesc函数类似，imshow函数可用于创建句柄图形图像对象。此外，该函数也可以自动设置各种句柄属性和图像特征，以优化显示效果。
1. imshow函数
当调用imshow函数显示图像时，将自动设置图形窗口、坐标轴和图像属性，以控制图像数据在MATLAB的解释方式。
在Matlab中，imshow函数的语法如下：
```matlab
imshow(I,n)
imshow(I,[low,high])
imshow(BW)
imshow(…,display_option)
imshow(x,y,A, …)
imshow filename
h=imshow(…)
```
根据用户使用参数的不同和MATLAB工具箱的设置，imshow函数在调用时除了完成前面提到的属性设置外，还可以：①设置其他的图形窗口对象和坐标轴对象的属性以定制显示效果。例如，可以通过设置隐藏坐标轴及其标示；②包含或隐藏图像边框；③调用函数以显示没有彩色渐变效果的图像。

2. 显示索引图像
利用imshow函数显示MATLAB的索引图像时，可以同时指定图像的数据矩阵和颜色映射表，形如：
```matlab
imshow(X,map)
```
其中，对于X中的每个像素，imshow都将其显示为存储在map映射表矩阵的相应的行所对应的颜色。

3. 显示灰度图像
调用imshow函数显示灰度图像的语法如下：
```matlab
imshow(I)
imshow(I,N)
```
其中：I为灰度图像数据矩阵，N为整数，用于指定对应于灰度颜色映射表中的索引数。
*例：
```matlab
I=imshow('windows.bmp');
imshow(I,64);      %绘制出具有64个灰度等级的灰度图
```
*例：
```matlab
I=imshow('windows.bmp');
imshow(I,2);       %绘制出具有2个灰度等级的灰度图，即黑白图。
```

4. 显示二进制位图
```matlab
imshow函数显示二进制位图的语法如下：
imshow(BW)
```
如果该位图的图像矩阵属于类double，则imshow函数将其显示为灰度图来对待，图像数据矩阵中值0所对应的像素显示为黑色，值1所对应的像素显示为白色。

5. 显示RGB图像
显示RGB图像的语法如下：
```matlab
imshow(RGB)
```
其中：RGB为一个m×n×3的图像数据矩阵。在Matlab中，该数据矩阵属于类double、类uint8或uint16。

6. 显示图形文件中的图像
通常情况下，在显示图像时，该图像的对象数据保存在MATLAB运行内存中的一个或多个变量中。但是，如果用户将图像保存在可以通过imread函数读取的图形文件中，则可通过下面的语法直接将其显示出来：
```matlab
imshow filename
```
如果图像是多帧的，那么imshow将仅仅显示第一帧，这种调用格式对于图像扫描非常有用。
注意：在使用这种格式时，该图形文件必须在当前目录下，或在MATLAAB目录下。
如果图像数据没有保存在MATLAB工作平台中，可以通过使用getimage函数将从当
前的句柄图形图像对象中获取图像数据。
*例：
```matlab
rgb=getimage;
```
下面的代码可以显示一幅小孩儿的图像：
```matlab
imshow kids.tif
```
7. 显示非图像数据
非图像数据：是指其数据矩阵的元素值落在“合法”范围之外。
对于double数组来说，该范围是[0,1]；
对于uint8数组来说，该范围是[0,255]；
对于uint16数组来说，该范围是[0,65 535]。
例：假设将一个灰度图进行过滤操作，则得到的结果数据可能在“合法”范围之外。此时显示该结果数据必须使用下面的语法：
```matlab
imshow(I,[low,high])
```
*例：先读取testpat.tif图形文件，然后对其进行过滤操作，再将结果数据显示出来：
```matlab
I=imread('testpat.tif');
J=filter([1 2;-1 -2],I);
imshow(I);
figure,imshow(J,[]);
```
### 特殊图像显示技术
在MATLAB的影像工具箱中，除了imshow函数外，还提供了一些实现特殊显示功能的函数。它们与MATLAB自身提供的图形函数相结合，为图像显示提供了各种特殊显示技术，包括有：
- 图像显示中添加颜色条；
 显示多帧图像阵列；
- 图像上的区域缩放；
- 将图像纹理映射到表面对象上；
- 显示多幅图像。

1. 添加颜色条；
在MATLAB的图像显示中，可以利用colorber函数将颜色条添加到坐标轴对象中。如果该坐标轴对象包含一个图像对象，则添加的颜色条将指示出该图像中不同颜色的数据值。
*例：先过滤一个类为uint8的图像，然后将其显示为灰度图，并添加颜色条：
```matlab
I=imread('saturn.tif');
h=[1 2 1;0 0 ;-1 -2 -1];
J=filter2(h,I);
imshow(J,[]);
colorbar;
```
2. 显示多帧图像阵列；
MTTLAB支持的多帧图像的文件格式包括HDF和TIFF两种。文件一旦被读入MATLAB，多帧图像的显示帧数由矩阵的第四维数值来决定。
在多阵列中查看图像，有下面几种方式：
①独立显示每一帧，调用imshow函数；
②同时显示所有的帧，调用montage函数；
③将多帧阵列转换为动画电影，调用immovie函数。

1)单帧显示
利用MATLAB标准的索引方法指定帧号，调用imshow函数，就可独立显示特定的帧。
例：
```matlab
load mri
imshow(D(:,:,:,7));
```
其中：D为MRI（磁共振图像）中的多帧图像阵列，调用imshow函数显示其中的第7帧。

2)多帧显示
调用montage函数可实现多帧显示，该函数的语法如下：
```matlab
montage(I)
montage(BW)
montage(X,map)
montage(…)
```
例：显示MRI的所有帧的代码如下：
```matlab
load mri
montage(D,map);
```
3)动画显示
利用immovie函数，可以从多帧图像阵列中创建Matlab电影动画。
值得注意的是：该函数只能应用于索引图像，所以，如果希望将其他类型的图像阵列转换为电影动画，则首先必须将该图像类型转换为索引类型。
例：
```matlab
mov=immovie(D,map);
colormap(map);
movie(mov)
```
3. 图像上的区域缩放；
利用zoom命令可实现图像上的任意区域的缩放。
在命令行中输入下面的代码：
```matlab
zoom on
```
回车执行后，matlab的图形窗口对象进入区域缩放状态。此时，按下鼠标左键，拖动鼠标指示，则图形窗口中将出现以虚线框表示的选择矩形。松开鼠标键后，则该选中的区域将被放大到整个图形窗口的显示空间。
在放大区域中单击鼠标右键可将刚刚放大的图形恢复到原来的状态。
如果命令行输入下面的代码：
```matlab
zoom off
```
则可关闭图形窗口的缩放功能。

4. 纹理映射
在Matlab中，专门提供了一个对图像进行纹理映射处理函数warp，使之显示在三维空间中。Wrap函数的语法格式如下：
```matlab
warp(X,map)
warp(I,n)
warp(BW)
warp(RGB)
warp(z,…)
warp(x,y,z,…)
h=warp(…)
```
在Matlab中，纹理映射是利用双线性渐变算法将图像映射到某个表面栅格上。
*例：
```matlab
[x,y,z]=cylinder;
I=imread('testpat1.tif');
warp(x,y,z,I);      %将testpat1.tif映射到圆柱体表面上。

```
有时图像可能不是按照所期望的形式进行纹理映射的，此时可以对纹理映射的外观进行修改，其方法之一就是修改坐标轴的Xdir、Ydir和Zdir属性值。

5. 显示多幅图像。
MATLAB没有对用户想要同时显示的图像数目进行限制，然而，由于受计算机硬件配置的影响，图像显示数目通常会存在一些系统限制。
显示多幅图像最简单的方法就是在不同的图形窗口中显示它们。imshow函数总是在当前窗口中显示一幅图像，如果想同时显示两幅图像，那么第二幅图像就会替代第一幅图像。为了避免图像在当前窗口中的覆盖现象，在调imshow函数之前可使用figure命令来创建一个新的空图形窗口。
例：
```matlab
imshow(I)
figure,imshow(I2)
figure,imshow(I3)
```
当采用该方法时，创建的图形窗口初始化是空白的。
如果使用的是8位显示系统，那么必须确保调色板人口的总数不超过256。
注意：灰度图像总是使用调色板来进行显示的，所以这些图像所使用的颜色通道总数不能超
过256。
为了避免产生同时显示图像的不正确的显示结果：
1)可采用对调色板进行操作的方法，使之使用较少的颜色
2)将图像转换为RGB格式再进行显示
3)使用ind2rgb函数将索引图像转换为RGB图像：imshow(ind2rgb(X,map))
4)简单使用cat命令将一幅灰度图像显示为一幅RGB图像：imshow(cat(3,I,I,I))

可以采用两种方法将多幅图像显示在同一个单独的图形窗口中。
①联合使用imshow函数和subplot函数；
②联合使用subimage函数和subplot函数；

subplot函数将一个图形窗口划分为多个显示区域，其语法格式为：
subplot(m,n,p)
这种格式将图形窗口划分为m×n个矩形显示区域，并激活第p个显示区域。
例：如果希望并排显示两幅图像，可使用以下语句：
```matlab
[X1,map1]=imread('forest.tif');
[X2,map2]=imread('trees.tif');
subplot(1,2,1),imshow(X1,map1);
subplot(1,2,2),imshow(X2,map2);
```
若共享调色板出现的显示结果不令人满意，可以使用subimage函数来显示，也可以在装载图像时将所有图像映射到同一个调色板中，这个调色板不是共享调色板情况下所采用的某一幅图像的调色板，而是映射后包含所有图像调色板信息的一个新调色板。
subimage函数在显示图像之前首先将图像转换为RGB图像，因此不会出现调色板问题。该函数的语法格式为：
```matlab
subimage(X,map)   %在一个窗口里显示多个索引图像。
subimage(I)       %在一个窗口里显示多个灰度图像。
subimage(RGB)     %在一个窗口里显示多个真彩色图像。
subimage(x,y,…)  %将图像按指定的坐标系(x,y)显示。
H=subimage(…)    %返回图像对象的句柄，其中输入的图像可以是uint8或double类型。
```
以下代码将显示与上面同样的两幅图像，其程序清单为：
```matlab
[X1,map1]=imread('forest.tif');
[X2,map2]=imread('trees.tif');
subplot(1,2,1),subimage(X1,map1);
subplot(1,2,2),subimage(X2,map2);
```


### 图像显示中的常见问题
1. 彩色图像显示为灰度图像
图像可能是一幅索引图像，这就意味显示这幅图像需要一个调色板。产生这个问题的原因可能是在装载索引图像时函数的调用方法不正确，正确调用格式如下：
```matlab
[X,map]=imread('filename.ext');

```
另外，还有注意使用imshow函数的正确形式：
```matlab
imshow(X,map);
```
2. 二值图像显示为全黑图像
    使用islogical或whos命令检查该图像矩阵的逻辑标志是否置为on。如果图像是逻辑的，那么whos命令将在类型头部单词array后面显示logical。如果二值图像是自己创建的，那么产生这个问题的原因可能是图像类型为uint8，记住uint8类型有灰度图像变换范围是[0,255]，而不是[0,1]。

3. 装载的是多帧图像，但是MATLAB却仅仅显示一帧图像
必须单独装载多帧图像的每一帧，可以使用一个for循环来实现。可以先调用imfinfo函数获知图像帧数和图像维数。


# 图像运算
## 图像的点运算
点运算(对比度增强、对比度拉伸、灰度变换)：是一种通过对图像中的每个像素(即像素点上
的灰度值)进行计算，从而改善图像显示效果的操作。
点运算常用于改变图像的灰度范围及分布，是图像数字化及图像显示的重要工具。
典型的点运算应用包括：
①光度学标定：通过对图像传感器的非线性特性做出补偿来反映某些物理特性，如光照强度、
光密度等；
②对比度增强：调整图像的亮度、对比度，以便观察；
③显示标定：利用点运算使得图像在显示时能够突出所有用户感兴趣的特征；
④图像分割：为图像添加轮廓线，通常被用来辅助后续运算中的边界检测；
⑤图像裁剪：将输出图像的灰度级限制在可用范围。
MATLAB图像处理工具箱没有提供对图像进行直接点运算的函数，而将图像的点运算过程直接集成在某些图像处理函数组中（如：直方图均衡化函数histeq和imhist）。如果用户仅仅是希望对图像进行点运算处理，那么可充分利用MATTAB强大的矩阵运算能力，对图像数据矩阵调用各种MATLAB计算函数进行处理。
*例：将灰度图像使用的灰度变换函数进行线性点运算的程序清单：
```matlab
rice=imread('rice.tif');
I=double(rice);
J=I*0.43+60;
rice2=uint8(J);
subplot(1,2,1),imshow(rice);
subplot(1,2,2),imshow(rice2);
```

## 图像的代数运算
图像的代数运算：是图像的标准算术操作的实现方法，是两幅输入图像之间进行点对点的加、减、乘、除运算后得到输出图像的过程。
MATLAB图像处理工具箱包含了一个能够实现所有非稀疏数值数据的算术操作的函数集合。
使用图像处理工具箱中的图像代数运算函数无须再进行数据类型间的转换，这些函数能够接受8位无符号类型或16位无符号类型数据，并返回相同格式的图像结果。
值得注意的是：无论进行哪一种代数运算都要保证输入图像的大小相等，且类型相同。
针对代数运算的结果很容易超出数据类型允许的范围，图像的代数运算函数使用了以下截取规则使运算结果符合数据范围的要求：超出范围的整数数据将被截取为数据范围的极值，分数结果将被四舍五入。

1. 图像的加法运算
图像相加一般用于对同一场景的多幅图像求平均效果（平均是指效果而言，并非算术平均），以便有效地降低具有叠加性质的随机噪声。
MATLAB中的imadd函数用于进行两幅图像的加法或给一幅图像加上一个常数。该函数将某一幅输入图像的每一个像素值与另一幅图像相应的像素值相加，返回相应的像素之和作为输出图像。其调用格式为：
```matlab
Z=imadd(X,Y)
```
其中，X和Y表示需要相加的两幅图像，返回值Z表示得到的加法操作结果。两幅图像的像素值相加时产生的结果很可能超过图像数据类型所支持的最大值（称为溢出），当数据发生溢出时，该函数将数据截取为数据类型所支持的最大值，这种截取效果称之为饱和，为了避免这种现象出现，在进行加法计算前最好将图像类型转换为一种数据范围较宽的数据类型。
例：两幅图像叠加
```matlab
I=imread('rice.png');
J=imread('cameraman.tif');
subplot(1,3,1),imshow(I);
subplot(1,3,2),imshow(J);
K=imadd(I,J);
subplot(1,3,3),imshow(K);
```
若不是两幅图像相加，而是给图像的每一个像素加上一个常数（使图像的亮度增加），同样可以采用imadd函数。
*例：RGB图像增加亮度
```matlab
RGB1=imread('flower.tif');
RGB2=imadd(RGB1,50);
subplot(1,2,1),imshow(RGB1);
subplot(1,2,2),imshow(RGB2);

RGB1=imread('rice.png');
RGB2=imadd(RGB1,50);
subplot(1,2,1),imshow(RGB1);
subplot(1,2,2),imshow(RGB2);
```

2. 图像的减法运算
图像减法也称为差分方法，是一种常用于检测图像变化及运动物体的图像处理方法。
在MATLAB中，imsubtract函数用来将一幅图像从另一幅输入图像中减去或从一幅图像中减去一个常数。该函数将一幅图像的像素值从另一幅输入图像相应的像素值中减去，再将相应的像素值之差作为输出图像相应的像素值。该函数的调用格式为：
```matlab
Z=imsubtract(X,Y)
```
其中，Z是输入图像X与输入图像Y相减的结果。
减法操作时有时会导致某些像素变为一个负数，此时，该函数自动将这些负数截取为0。为了避免差值产生负值及像素值运算结果之间产生差异，可以调用imabsdiff函数，该函数将计算两幅图像相应像素差值的绝对值，其调用格式与imsubtract函数类似。
例：根据原始图像生成其背景亮度图像，然后再从原始图像中将背景亮度图像减去
```matlab
rice=imread('rice.png');
background=imopen(rice,strel('disk',15));
rice2=imsubtract(rice,background);
subplot(1,2,1),imshow(rice);
subplot(1,2,2),imshow(rice2);
```
若希望从图像数据I的每一像素中减去一个常数，可以将上述调用格式中的Y替换为一个指定的常数值，如：Z=imsubtract(I,50)

3. 图像的乘法运算
两幅图像进行乘法运算可以实现掩模操作，即屏蔽掉图像的某些部分。一幅图像乘以一个常数通常称为缩放。缩放通常将产生比简单添加像偏移量自然得多的明暗效果。如果使用的缩放因数大于1，那么将增强图像的亮度，如果因数小于1，则会使图像变暗。
在MATLAAB中，使用immultiply函数实现两幅图形的乘法。该函数将两幅图像相应的像素值进行元素对元素的乘法，并将乘法的运算结果作为输出图像相应的像素值。其操作时将产生溢出现象，为了避免该现象产生，在执行前可将图像类型转换为一种数据范围较宽的数据类型。该函数的调用格式为：
```matlab
Z=immultiply(X,Y)
```
其中，Z=X*Y。
例：使用给定的缩放因数对moon.tif的图像进行缩放的程序清单：
```matlab
I=imread('moon.tif');
J=immultiply(I,1.2);
subplot(1,2,1),imshow(I);
subplot(1,2,2),imshow(J);
```

4. 图像的除法运算
图像除法运算又称为比率变换，给出的是相应像素值的变化比率，而不是每个像素的绝对差异，可用于校正成像设备的非线性影响。
在MATLAB中使用imdivide函数进行两幅图像的除法，该函数对两幅输入图像的所有相应像素执行元素对元素的除法操作，并将得到的结果作为输出图像的相应像素值。其调用格式为：
```matlab
Z=imdivide(X,Y)
```
其中，Z=X/Y。
例：将rice.tif的两幅图像进行除法运算的程序清单：
```matlab
rice=imread('rice.png');
background=imopen(rice,strel('disk',15));
rice2=imsubtract(rice,background);
subplot(1,3,1),imshow(rice);
subplot(1,3,2),imshow(rice2);
Ip=imdivide(rice,rice2);
subplot(1,3,3),imshow(Ip);
```

5. 图像的四则代数运算
执行图像四则代数运算操作较好的一个办法是使用函数imlincomb，该函数按照双精度执行所有代数运算操作，而且仅对最后的输出结果进行截取，其调用格式为：
```matlab
Z=imlincomb(A,X,B,Y,C)
```
其中，Z=A*X+B*Y+C。MATLAB会自动根据输入参数判断需要进行的运算。


## 图像几何运算
在处理图像的过程中，有时需要对图像的大小和几何关系进行调整，如：对图像进行缩放及旋转，这时图像中每个像素的值都要发生变化。数字图像的坐标是整数，经过这些变换之后的坐标不一定是整数，因此要对变换之后的整数坐标位置的像素值进行估计。
MATLAB提供了一些函数实现这些功能。这些函数支持所有的图像类型，可实现对图像进行缩放、旋转、裁剪等几何操作。
1. 图像的插值
插值是常用的数学运算，通常是利用曲线拟合的方法，通过离散的采样点建立一个连续函数来逼近真实曲线，用这个重建的函数便可求出任意的函数值。
设已知函数值为 则未知点x的函数值通过插值可以表示为：
 
其中h(•)为插值核函数， 为权系数。插值算法的数值精度及计算量与插值核函数有关，插值核函数的设计是插值算法的核心。
MATLAB中的imresize函数和imrotate函数用于二维图像的插值。MATLAB影像处理工具箱提供了三种插值方法：
①最近邻插值（nearest neighbor interpolation）
②双线性插值（bilinear interpolation）
③双立方插值（bicubic interpolation）

1) 最近邻插值：是最简单的插值，在这种算法中，每一个插值输出像素的值就是在输入图像中与其最临近的采样点的值。该算法的数学表示为：
 
最近邻插值是工具箱函数默认使用的插值方法，而且这种插值方法的运算量非常小。对于索引图像来说，它是惟一可行的方法。不过，最近邻插值法的值核频域特性不好，从它的傅立叶谱上可以看出，它与理想低通滤波器的性质相差较大。当图像含有精细内容，也就是高频分量时，用这种方法实现倍数放大处理，在图像中可以明显看出块状效应。

2) 双线性插值：该方法输出像素值是它在输入图像中2×2邻域采样点的平均值，它根据某像素周围4个像素的灰度值在水平和垂直两个方向上对其插值。

3) 双立方插值：该种插值核为三次函数，其插值邻域的大小为4×4。它的插值效果比较好，但相应的计算量较大。
这三种插值方法的运算方式基本类似。对于每一种来说，为了确定插值像素点的数值，必须在输入图像中查找到与输出像素相对应的点。这三种插值方法的区别在于其对像素点赋值的不同。其中近邻插值输出像素的赋值为当前点的像素点；双线性插值输出像素的赋值为2×2矩阵所包含的有效点的加权平均值；双立方插值输出像素的赋值为4×4矩阵所包含的有效点的加权平均值。

2. 图像大小调整
利用imresize函数通过一种特定的插值方法可实现图像大小的调整。该函数的语法如下：
```matlab
B=imresize(A,m,method)   
B=imresize(A,[mrows,ncols],method)
B=imresize(…, method,n)
B=imresize(…,method,h)
```
这里参数method用于指定插值的方法，可选的值为‘nearest’、‘bilinear’、‘bicubic’，如果没有指定插值方法，则该函数将采用缺省的近邻插值（nearest）方法。
上述第一种返回图像大小等于A的大小乘以放大系数m，若放大系数m设置在0到1之间，则B比A小，即图像缩小；若放大系数m设置在大于1，则图像放大。

第二种语法返回一个mrows行、ncols列的图像，若mrows和ncols定义的长度比原图不同，则图像会产生变形。
在使用bilinear和bicubic方法缩小图像时，为消除引入的高频成分，imresize使用一个前端平滑滤波器，默认的滤波器尺寸为11×11。

也可以通过参数n指定滤波器的尺寸，即为上述第三种语法结构。对于mearest插值方法，imresize不使用前端滤波器，除非函数明确指定。

第四种语法结构是使用用户设计的插值核h进行插值，h可以看作一个二维FIR滤波器，

例：使用不同的插值方法对图像进行放大的程序清单：
```matlab
load woman2
subplot(2,2,1),imshow(X,map);
X1=imresize(X,2,'nearest');
subplot(2,2,2),imshow(X1,[]);
X2=imresize(X,2,'bilinear');
subplot(2,2,3),imshow(X2,[]);
X3=imresize(X,2,'bicubic');
subplot(2,2,4),imshow(X3,[]);
```
由图可见，在进行小倍数放大时，最近邻插值方法的效果还可以，双线性插值方法的结果有些模糊，双立方插值效果最好。

3. 图像旋转
在对数字图像进行旋转的时候，各像素的坐标会发生变化使得旋转之后不能正好落在整数坐标处，需要进行插值。在工具箱中的函数imrotate可用上述三种方法对图像进行插值旋转，利用imrotate函数可以通过一种特定的插值方法来改变图像的显示角度。该函数的语法格式如下：
```matlab
B=imrotate(A,angle,method)
```
使用指定的插值方法（同imresize函数中的插值方法）逆时针方向将图像A旋转angle角度。返回图像B通常大于A，包含整个旋转图像。若对图像进行顺时针旋转，则angle取负值。一般来说，旋转后的图像会比原来图大，超出原来图像的部分值为0，为了使返回的图像与原来图像大小相同，可采用如下的格式：
```matlab
B=imrotate(A,angle,method,’crop’)
```
其功能是：通过指定crop参数对旋转后的图像进行剪切（取图像的中间部分），把图像进行angle角度旋转，然后返回和A大小相同的中间部分。

例：将flowers.tif图像插值旋转350的程序清单：
```matlab
I=imread('flowers.tif');
J=imrotate(I,35,'bilinear');
subplot(1,2,1),imshow(I);
subplot(1,2,2),imshow(J);

I=imread('rice.png');
J=imrotate(I,35,'bilinear');
subplot(1,2,1),imshow(I);
subplot(1,2,2),imshow(J);
```
4. 图像剪裁
在进行图像处理过程中，有时只需要处理图像中的一部分，或者需要将某某部分取出，这样就要对图像进行剪切。工具箱中的imcrop函数将图像剪裁成指定矩形区域。该函数的语法如下：
```matlab
I2=imcrop(I)
X2=imcrop(X,map)
RGB2=imcrop(RGB)
```
其功能是：交互式地对灰度图像、索引图像和真彩色图像进行剪切，显示图像，允许用鼠标指定剪裁矩形。
```matlab
I2=imcrop(I,rect)
X2=imcrop(X,map,rect)
RGB2=imcrop(RGB,rect)
```
其功能是：非交互式指定剪裁矩阵，按指定的矩阵框rect剪切图像，rect为四元素向量[xmin,ymin,width,height]，分别表示矩形的左下角和长度及宽度，这些值在空间坐标中指定。
```matlab
[…]=imcrop(x,y, …)
```
其功能是：在指定坐标系(x,y)中剪切图像。
```matlab
[A,rect]=imcrop(…)
[x,y,A,rect]=imcrop(…)
```
其功能是：在用户交互剪切图像的同时返回剪切框的参数rect。
*例：从ic,tif图像中剪取鼠标左键拖动选取的矩形区域，并以新的图形窗口显示出来的程序清单：
```matlab
imshow ic.tif;
I=imcrop;
imshow(I);

imshow kids.tif;
I=imcrop;
figure;imshow(I);
```

## 图像邻域和块操作
输出图像中的每个像素值都是对应的输入像素及其某个邻域内的像素共同决定的，这种图像运算称为邻域运算。
通常邻域是指一个远远小于图像尺寸的形状规则的像素块，例如：2×2、3×3、4×4的正方形，或用来近似表示圆及椭圆等形状的多边形。一幅图像所定义的所有邻域应该具有相同的大小。
邻域运算与点运算一起形成了最基本、最重要的图像处理方法，尤其是滑动邻域操作，经常被用于图像的线性滤波和二值形态操作。
邻域操作包括滑动邻域操作和分离邻域操作（图像块操作）两种类型。
在进行滑动邻域操作时，输入图像将以像素为单位进行处理，也就是说，对于输入图形的每一个像素，指定的操作将决定输出图像相应的像素值。
分离邻域操作（图像块操作）是基于像素邻域的数值进行的，输入图像一次处理一个邻域，即图像被划分为矩阵邻域，分离邻域操作将分别对每一个邻域进行操作，求取相应输出邻域的像素值。

1. 滑动邻域操作
在MATLAB中，滑动邻域是一个像素集，像素集包含的元素由中心像素的位置决定。滑动邻域操作一次只处理一个图像像素。当操作从图像矩阵的一个位置移动到另一个位置时，滑动邻域也以相同的方向运动。
通常，对于m×n的滑动邻域来说，中心像素的计算方法为：
```matlab
floor(([m,n]+1)/2)
```

在MATLAB进行滑动邻域操作的过程如下：
①选择像素；
②确定该像素的滑动邻域；
③调用适当的函数对滑动邻域中的元素进行计算；
④查找输出图像与输入图像对应处的像素，将该像素的数值设置为上一步中得到的返回值。即将计算结果作为输出图像中对应的像素的值；
⑤对输入图像的每一个像素点，重复1)到4)的操作。

MATLAB提供的几种用于邻域操作的函数：

1)colfilt函数：该函数用于快速的邻域操作，其调用格式为：
```matlab
B=colfilt(A,[m n],block_type,fun)
```
其功能是：实现快速的邻域操作，图像的尺寸为m×n，block_type为指定块的移动方式，即，当为’distinct’时，图像块不重叠；当为’sliding’时，图像块滑动。fun为运算函数，其形式为y=fun(x)。
```matlab
B=colfilt(A,[m n],block_type,fun，P1,P2)
```
其功能是：指定fun中除x以外的其他参数P1、P2、…。
```matlab
B=colfilt(A,[m n],[mblock nblock],block_type,fun,…)
```
其功能是：为节省内存按mblock×nblock的图像块对图像A进行块操作。

例：下面是一个对图像alumgrns.tif进行滑动平均操作程序清单：
```matlab
I=imread('alumgrns.tif');
I2=colfilt(I,[5 5],'sliding','mean');
imshow(I);
figure,imshow(I2,[]);

I=imread('rice.png');
I2=colfilt(I,[5 5],'sliding','mean');
imshow(I);
figure,imshow(I2,[]);
```

对于滑动邻域操作，colfilt函数为图像中每个像素建立一个列向量，向量的各元素对应该像素的邻域元素。
colfilt函数可以根据需要对图像进行补零 。
colfilt函数生成的临时矩阵被传递给自定义函数，自定义函数为矩阵的每一列返回一个单独的值。MATLAB中很多函数具有这种功能（如：mean、std），返回值赋给输出图像中对应的像素。
例：对输入图像处理，输出图像为每个像素邻域的最大值。
```matlab
I=imread('rice.png');
f=inline('max(x)');
J=colfilt(I,[8 8],'sliding',f);
imshow(I);
figure,imshow(J);
```

对于图像块操作，colfilt函数把每个图像块排列成一列，构成一个临时矩阵。如果需要，可以对图像进行补零。
colfilt函数把原始图像排列成临时矩阵之后，将其传入自定义函数，自定义函数必须返回和临时矩阵大小相同的矩阵。然后colfilt函数再把结果重新排列成原始图像的格式。

例：利用colfilt函数把输入图像8×8的图像块均值赋予图像块中所有元素的程序清单：
```matlab
I=imread('saturn.tif');
imshow(I)
f=inline('ones(64,1)*mean(x)');
I2=colfilt(I,[8 8],'distinct',f);
figure,imshow(I2,[])

I=imread('rice.png');
imshow(I)
f=inline('ones(64,1)*mean(x)');
I2=colfilt(I,[8 8],'distinct',f);
figure,imshow(I2,[])
```

2) nlfilter函数：该函数是通用的滑动窗操作函数，其语法格式为：
```matlab
B=nlfilter(A,[m n],fun)
```
它是一个通用的滑动窗操作，图像块的尺寸为m×n。
```matlab
B=nlfilter(A,[m n],fun, 
P1,P2,…)
```
其中，A表示输入图像，[m n]指定邻域大小，fun是一个返回值为标量的计算函数，如果该计算函数需要参数，那么参数P1、P2、…将紧跟在fun参数后。返回值B是一个与输入图像相同大小的图像矩阵。
```matlab
B=nlfilter(A,’indexed’,…)
```
它是用于对索引图像的滑动窗操作。

例：调用nlfilter函数进行滑动操作程序清单：
```matlab
I=imread('tire.tif');
f=inline('max(x(:))');
J=nlfilter(I,[3 3],f);
subplot(1,2,1),imshow(I);
subplot(1,2,2),imshow(J);
```

2. 图像块操作
图像块操作是将图像的数据矩阵划分为同样大小的矩形区域的操作，它是图像分析和图像压缩的基础。同时由于图像划分为图像块后可以转化为矩阵或者向量运算，因此可以大大加快图像处理的速度。
MATLAB进行图像块操作的函数有：
1) blkproc函数：该函数能够将每个显示块从影像中提取出来，然后将其作为参数传递给任何用户函数量（即用户指定的函数）。此外，blkproc函数还将由用户函数返回的显示块进行组合，从而生成最后的输出图像。其语法格式如下：
```matlab
B=blkproc(A,[m n],fun)
```
其功能是：对图像A的每个不同m×n块应用函数fun进行处理，必要时补加0。fun为运算函数，其形式为y=fun(x)，可以是一个包含函数名的字符串，或表达式的字符串。另外，还可以将用户函数指定为一个嵌入式函数（即inline函数）。在这种情况下，出现在blkproc函数中的嵌入式函数不能带有任何引用标记。
```matlab
B=blkproc(A,[m n],fun,P1,P2,…)
```
其功能是：指定fun中除x以外的其他参数P1、P2、…。
```matlab
B=blkproc(A,[m n],[mborder nborder],fun,…)
```
其功能是：指定图像块的扩展边界mborder和nborder，实际图像块大小为(m+2×mborder)×(n+2×nborder)。允许进行图像块操作时，各图像块之间有重叠。也就是说，在对每个图像块进行操作时，可以为图像块增加额外的行和列。当图像块有重叠时，blkproc函数把扩展的图像块传递给自定义的函数。
```matlab
B=blkproc(A,’index’,…)
```
它是用于对索引图像的块操作。
例：计算图像8×8区域的局部标准差的程序清单：
```matlab
I=imread('tire.tif');
f=inline('uint8(round(std2(x)*ones(size(x))))');
I2=blkproc(I,[8 8],f);
subplot(1,2,1),imshow(I);
subplot(1,2,2),imshow(I2);
```
当需要进行邻域之间相互重叠时，在进行邻域处理时要重点考虑重叠部分的像素值。为了实现重叠方法，可利用以下语句：
```matlab
*B=blkproc(A,[4 8],[1 2],’fun’)
```

2) bestblk函数：该函数用于选择图像块的尺寸，其语法格式为：
```matlab
siz=bestblk([m n],k)
```
其功能是：返回对尺寸为m×n的图像的块划分siz，k为图像块长度和宽度的最大值。
```matlab
[mb,nb]=bestblk([m n],k)
```
其功能是：返回mb和nb分别为图像块的行数和列数。

3) col2im函数：该函数用于将向量重新排列成图像块，其作用在于提高其运算速度。但是处理完后还需将向量排列成矩阵。其语法格式为：
```matlab
B=col2im(A,[m n],[mm nn],block_type)
```
其功能是：将图像A的每一列重新排列成m×n的图像块，block_type为指定排列的方式，即：当block_type为distinct时，图像块不重叠；当block_type为sliding时，图像块滑动。用这些图像块组合成mm×nn的图像A。

4) im2col函数：该函数实现将图像块排列成向量的功能，其语法格式为：
```matlab
B=im2col(A,[m n], block_type)
```
其功能是：将图像A的每一个m×n块转化成一列，重新组合成图像B。block_type为指定排列的方式，即：当block_type为distinct时，图像块不重叠；当block_type为sliding时，图像块滑动。
```matlab
B=im2col(A,[m n])
B=im2col(A,’index’,…)
```
它是用于对索引图像块排列成向量的操作。


# 图像分析
MATLAB的影像处理工具箱支持多种标准的图像处理操作，以方便用户对图像进行分析和调整。这些图像处理操作主要包括：
①获取像素值及其统计数据；
②分析图像，抽取其主要结构信息；
③调整图像，突出其某些特征或抑制噪声


## 像素值及其统计
MATLAB的影像处理工具箱提供了多个函数以返回与构成图像的数据值相关的信息，这些函数能够以多种形式返回图像数据的信息，主要包括：
①选定像素的数据值（pixval函数和impixel函数）；
②沿图像中某个路径的数据值（improfile函数）；
③图像数据的轮廓图（imcontour函数）；
④图像数据的柱状图（imhist函数）；
⑤图像数据的摘要统计值（mean2函数、std2函数和corr2函数）；
⑥图像区域的特征度量（imfeature函数）

1. 像素选择
影像处理工具箱中包含两个函数可返回用户指定的图像像素的颜色数据值。
1) pixval函数
当光标在图像上移动时，该函数以交互的方式显示像素的数据值。另外，该函数还可以显示两个像素之间的Euclidean距离。

2) impixel函数
impixel函数可以返回选中像素或像素集的数据值。用户可以直接将像素坐标作为该函数的输入参数，或用鼠标选中像素。
例：
```matlab
imshow canoe.tif;
val=impixel
```
对于索引图像，pixel函数和impixel函数都将其显示为存储在颜色映像中的RGB值而不是索引值。

2. 强度描述图
在MATLAB影像处理工具箱中，提供了improfile函数用于沿着图像中一条直线段路径或直线路径计算并绘制其强度（灰度）值。
例：
```matlab
imshow debyel.tif;
improfile

imshow canoe.tif;
improfile
```

例：
```matlab
RGB=imread('flowers.tif');
figure(1);imshow(RGB);
improfile
```

3. 图像轮廓图
在灰度图的轮廓图显示时，可利用MATLAB影像处理工具箱中的imcontour函数。该函数类似于contour函数，与contour函数相比，其功能更全。它能够自动设置坐标轴对象，从而使得其方向和纵横比能够与所显示的图形相匹配。
例：
```matlab
I=imread('rice.tif');
imshow(I);
figure;imcontour(I)

I=imread('rice.png');
imshow(I);
figure;imcontour(I)
```

4. 图像柱状图
图像柱状图可以用来显示索引图像或灰度图像中的灰度分布。可利用MATLAB影像处理工具箱中的imhist函数创建柱状图。
例：以前面介绍的大米灰度图为例来创建该图的柱状图。其代码如下：
```matlab
I=imread('rice.tif');
imhist(I,64);

I=imread('rice.png');
imhist(I,64);
```


## 图像分析
MATLAB中的图像分析技术可以提取图像的结构信息。例如，可以利用影像处理工具箱提供的edge函数来探测边界。这里所谓的边界，其实就是图像中包含的对象所对应的位置。下面介绍几种常见图像分析函数。
1. 灰度图像的边缘：edge函数
该函数的语法如下：
```matlab
BW=edge(I,method)
```

返回与I大小一样的二进制图像BW，其中元素I为发现I中的边缘。method为下列字符串之一：
‘sobel’：缺省值，用导数的sobel近似值检测边缘，那些梯度最大点返回边缘；
‘prewitt’：用导数的prewitt近似值检测边缘，在那些梯度最大点返回边缘；
‘roberts’：用导数的roberts近似值检测边缘，在那些梯度最大点返回边缘；
‘log’：使用高斯滤波器的拉普拉斯运算对I进行滤波，通过寻找0相交检测边缘。
‘zerocross’：使用指定的滤波器对I滤波后，寻找0相交检测边缘。

```matlab
BW=edge(I,method,thresh)
```
用thresh指定灵敏度阈值，所有不强于thresh的边缘都被忽略。
```matlab
BW=edge(I,method,thresh,direction)
```
对于’sobel’和’prewitt’方法指定方向；
direction为字符串：’horizontal’表示水平方向，’vertical’表示垂直方向，’both’两个方向（缺省值）。 
```matlab
BW=edge(I,’log’,thresh,sigma)
```
用sigma指定标准偏差。
```matlab
[BW,thresh]=edge(…)。
```
2. 行四叉树分解：qtdecomp函数
将一块图像分成四块等大小的方块，然后判断每块是否满足同性质的标准，如果满足，则不再分解，否则，再进行细分成四块，并对每块应用测试标准，分解过程重复迭代下去，直到满足标准，结果可能包含不同大小的块。该函数的语法结构如下：
```matlab
S=qtdecomp(I)
```
对灰度图像I进行四叉树分解，返回四叉树结构的稀疏矩阵S。
```matlab
S=qtdecomp(I,threshold)
```
如果块中元素最大值减去最小值大于threshold，则分解块。threshold为0到1之间的值。
```matlab
S=qtdecomp(I，threshold,mindim)
```
如果块小于mindim就不再分解，无论其符合阈值条件与否
```matlab
S=qtdecomp(I，threshold,[mindim maxdim])
```
如果块小于mindim或大于maxdim就不再分解，maxdim/mindim必须为2 的幂。
```matlab
S=qtdecomp(I,FUN)
```
使用函数FUN确定是否分解块。
```matlab
S=qtdecomp(I,FUN,P1,P2,…)
```

3. 获取四叉树分解块值：qtdgetblk函数
该函数的语法结构如下：
```matlab

[VALS,R,C]=qtdgetblk(I,S,dim)
```
VALS中对应dim×dim块的值取代I的四叉树分解中的每个dim×dim块。S由qtdecomp函数返回的稀疏矩阵，包含四叉树结构；VALS是dim×dim×k数组，k是四叉树的分解的dim×dim块的数量。如果没有指定大小的块，则返回一个空矩阵。R和C为包含块左上角行列坐标的向量。
```matlab
[VALS,IDX]=qtdgetblk(I,S,dim)
```
返回块左上角直线索引的向量IDX。

4. 设置四叉树分解块值：qtsetblk函数
```matlab
J=qtsetblk(I,S,dim,VALS)
```
用VALS中对应dim×dim块的值取代I的四叉树分解中的每个dim×dim块。S由qtdecomp函数返回的稀疏矩阵，包含四叉树结构；VALS是dim×dim×k数组，k是四叉树的分解的dim×dim块的数量。

5. 实例
1)图像分析中的灰度边缘检测实例
```matlab
%调入与显示RGB图像
*RGB=imread('flowers.tif');
isrgb(RGB);
figure(1);imshow(RGB);

RGB=imread('autumn.tif');
isrgb(RGB);
figure(1);imshow(RGB);

% RGB图像转换为灰度图像
I=rgb2gray(RGB);
figure(2);imshow(I);
colorbar('horiz');
isgray(I);

% 边缘检测
ED=edge(I,'sobel',0.08);
figure(3);imshow(ED);
```

2) Sobel边界探测器和Canny边界探测器在图像分析中的应用实例
操作的对象仍以前面提到rice.tif图像为例。其代码如下：
```matlab
I=imread('rice.tif');

I=imread('rice.png');
BW1=edge(I,'sobel');
BW2=edge(I,'canny');
figure(1);imshow(BW1);
figure(2);imshow(BW2);
```

## 图像调整
MATLAB中的图像高速技术用于图像的改善。此处的“改善”有两个方面的含义，即：客观方面，例如提高图像的信噪比；主观方面，例如通过修正图像的颜色和强度（灰度）使其某些特征更容易辨识。
1. 对比度增强
在MATLAB中，有关函数有：
1) 对比度调整函数：imadjust函数
该函数可用于调整灰度值或颜色图，其用法为：
```matlab
J=imadjust(I,[low high],[bottom top],gamma)
```
将灰度图像I转换为图像J，使值从low到high与从bottom到top相匹配。值大于high或小于low的被剪去，即小于low的值与bottom相匹配，大于high的值与top相匹配。使用该函数时可将[low high]或[bottom top]指定为空矩阵[ ]，此时缺省值为[0 1]。Gamma用来指定描述I和J值关系曲线的形状；gamma < 1，越亮输出值越加强；gamma > 1，越亮输出值越减弱；缺省gamma=1，表示线性变换。
```matlab
newmap=imadjust(map,[low high],[bottom top],gamma)
```
对索引图像的颜色图进行变换。如果[low high]和[bottom top]均为2×3矩阵，则gamma为1×3向量，imadjust函数分别调整红、绿、蓝成分，调整后的颜色图newmap大小与原来的map一样。
```matlab
RGB=imadjust(RGB1,…)
```
对RGB图像RGB1的每个图像块进行调整。与调整颜色图一样，通过指定[low high]和[bottom top]均为2×3矩阵，gamma为1×3向量，对每个图像块可以使用不同的参数值。如果top < bottom，则图像颜色或灰度将倒置，即倒置变换，得到原图的底片。输入图像可以是uint8或双精度类型值，输出图像与输入图像类型一样。

2) 函数：brighten函数
该函数的用法为：brighten(beta)
使现有颜色图变成更亮或更暗的图。如果0 < beta ≤1，则颜色图增亮；－1≤beta < 0，则颜色图变暗。brighten（beta）可以使用brighten（-beta）还原。

```matlab
MAP=brighten(beta)
```
返回当前使用的颜色图的更亮或更暗变换后的颜色图MAP，但不改变现有的显示。
```matlab
NEWMAP=brighten(MAP,beta)
```
返回指定颜色图MAP的更亮或更暗变换后的新颜色图NEWMAP，但不改变显示。
```matlab
brighten(FIG,beta)
```
增强图FIG的所有物体。

3) 直方图调整法
在MATLAB中，histeq函数用直方图均衡增强对比度。直方图均衡通过转换灰度图像亮度值或索引图像的颜色图值来增强图像对比度，输出图像的直方图近似与给定的直方图相匹配。
```matlab
J=histeq(I,hgram)
```
转换灰度图像I，使输出图像J的直方图具有length(hgram)个条，近似与hgram相匹配。向量hgram包含等间隔条灰度值的整数计数个数。
```matlab
J=histeq(I,N)
```
将灰度图像I转化成具有N个离散灰度级的灰度图像J，N缺省值为64。
```matlab
[J,T]=histeq(I)
```
返回灰度级变换，使J的灰度级与I的灰度级相匹配。
```matlab
NEWMAP=histeq(X,MAP,hgram)
```
变换索引图像X的颜色图，使索引图像(X,NEWMAP)的灰度级成分与hgram相匹配。返回变换后的颜色图NEWMAP，length(hgram)必须与size(MAP,1)一样。
输入图像可以是uint8或双精度类型。输出颜色图通常为双精度类型。输出T也是双精度类型。

2. 图像平滑
图像平滑主要用于受干扰而质量降低的图像，在MATLAB图像处理工具箱中有关图像噪声的函数有：
1) 向图像增加噪声：imnoise函数
该函数的用法为：
```matlab
J=imnoise(I,type,…)
```
向灰度图像I中增加type类型噪声。Type为下列字符串之一：
‘gaussian’：增加GAUSS白噪声；
‘salt & pepper’：增加黑白像素点；
‘speckle’：增加乘法噪声。
根据类型再确定其他参数。
```matlab
J=imnoise(I, ‘gaussian’,M,V)
```
在图像I中加入均值为M、方差为V的高斯白噪声。缺省值为0，方差为0.01的噪声。
```matlab
J=imnoise(I, ‘salt & pepper’,D)
```
在图像I中加入强度为D的“树盐”黑白像素点。其效果近似于：D*prod(size(I))像素。缺省强度为0.05。
```matlab
J=imnoise(I, ‘speckle’,V)
```
使用公式J=I+n*I，向图像I中加入乘法噪声，其中n是均值为0，方差为V的均匀分布随机噪声。V缺省值为0.04。
图像I类型为uint8或双精度值，输出图像J与I类型一致。

2) 二维中值滤波器：medfilt2函数
```matlab
B=medfilt2(A,[M N])
```
对矩阵A进行二维中值滤波。每个输出像素包含输入图像中相应像素周期的M×N邻域的中值。在图像边缘添加0，因此边缘在[M N]/2内的点可能发生扭曲。[M N]缺省值为[3 3]。
```matlab
B=medfilt2(A,’indexed’,…)
```
将A当作索引图像处理，如果A为uint8类，填补0；如果A为双精度类，则填补1。

3) 状态统计滤波器：ordfilt2函数
```matlab
Y=ordfilt2(X,order,domain)
```
由domain中非0元素指定邻域的排序集中的第order个元素代替X中的每个元素。Domain是一个仅包括0和1的矩阵，1仅定义滤波运算的邻域。
```matlab
Y=ordfilt2(X,order,domain,S)
```
S与domain一样大，用与domain的非0值相应的S的值作为附加补偿。

4)二维自适应除噪滤波器：wiener2函数
wiener2函数估计每个像素的局部均值与方差，该函数用法如下：
```matlab
J=wiener2(I,[M N],noise)
```
使用M×N大小邻域局部图像均值与偏差，采用像素式自适应滤波器对图像I进行滤波。
```matlab
[J,noise]=wiener2(I,[M N])
```
滤波前还有估计附加噪声的能量。


# 特定区域处理
## 区域的指定
在进行图像处理时，有时只要对图像中某个特定区域进行处理，并不需要对整个图像进行处理。MATLAB中对特定区域的处理是通过二值掩模来实现的，通过选定一个区域后会生成一个与原图大小相同的二值图像，选定的区域为白色，其余部分为黑色。通过掩模图像，就可以实现对特定区域的选择性处理。下面介绍创建区域的方法：
1. 多边形选择方法
roipoly函数用于设定图像中的多边形区域，该函数返回与输入图像大小一致的二值图像BW，选中的区域值为1，其余的部分值为0。其语法格式为：
```matlab
BW=roipoly(I,c,r)
```
其功能是：用向量c、r指定多边形各角点的X、Y轴的坐标。
```matlab
BW=roipoly(I)
```
其功能是：是让用户交互选择多边形区域，通过点击鼠标设定多边形区域的角点，用空格键和Del键撤销选择，按Enter键确认选择，确认后该函数返回与输入图像大小一致的二值图像BW，在多边形区域内像素值为1，其余区域内像素值为0。
```matlab
BW=roipoly(x,y,I,xi,yi)
```
其功能是：是用矢量x、y建立非默认的坐标系，然后在指定的坐标系下选择由向量xi、yi指定的多边形区域。
```matlab
[BW,xi,yi]=roipoly(…)
```
其功能是：交互选择多边形区域，并返回多边形角点的坐标。
```matlab
[x,y,BW,xi,yi]=roipoly(…)
```
其功能是：交互选择多边形区域后，还返回多边形顶点在指定的坐标系X－Y下的坐标。

例：根据指定的坐标选择一个六边形区域的程序清单：
```matlab
I=imread('eight.tif');
c=[222 272 300 272 222 194];
r=[21 21 75 121 121 75];
BW=roipoly(I,c,r);
figure(1);imshow(I);
figure(2);imshow(BW);
```

2. 其他选择方法
MATLAB图像处理工具箱中提供了可以实现按灰度选择区域的函数roicolor函数，其语法格式为：
```matlab
BW=roicolor(A,low,high)
```
其功能是：按指定的灰度范围分割图像，返回二值掩模BW，[low,high]为所要选择区域的灰度范围。如果low大于high，则返回为空矩阵。
```matlab
BW=roicolor(A,v)
```
其功能是：按向量v中指定的灰度值来选择区域。
下面是一个按灰度分割图像中的目标的程序清单：
```matlab
I=imread('rice.tif');

I=imread('rice.png');
BW=roicolor(I,128,255);
figure(1);imshow(I);
figure(2);imshow(BW);
```

## 特定区域滤波
MATLAB图像处理工具箱中提供的roifilt2函数用于对特定区域进行滤波，其语法格式为：
```matlab
J=roifilt2(h,I,BW)
```
其功能是：使用滤波器h对图像I中用二值掩模BW选中的区域滤波。
```matlab
J=roifilt2(I,BW,fun)
J=roifilt2(I,BW,fun,P1,P2,…)
```
其功能是：对图像I中用二值掩模BW选中的区域作函数运算fun，其中fun是描述函数运算的字符串，参数为P1、P2、…。返回图像J在选中区域的像素为图像I经fun运算的结果，其余部分的像素值为I的原始值。

例：对指定区域进行锐化滤波的程序清单：
```matlab
I=imread('eight.tif');
c=[222 272 300 272 222 194];
r=[21 21 75 121 121 75];
BW=roipoly(I,c,r);
h=fspecial('unsharp');
J=roifilt2(h,I,BW);
subplot(1,2,1);imshow(I);
subplot(1,2,2);imshow(J);
```
由运行结果可知：右上角的硬币发生了变化，而其他硬币保持不变。


## 特定区域填充
MATLAB图像处理工具箱中提供的roifill函数用于对特定区域进行填充，其语法格式为：
```matlab
J=roifill(I,c,r)
```
其功能是：填充由向量c、r指定的多边形，c和r分别为多边形各顶点的X、Y坐标。它是通过解边界的拉普拉斯方程，利用多边形边界的点的灰度平滑的插值得到多边形内部的点。通常可以利用对指定区域的填充来“擦”掉图像中的小块区域。
```matlab
J=roifill(I)
```
其功能是：由用户交互选取填充的区域。选择多边形的角点后，按Enter键确认选择，用空格键和Del键表示取消一个选择。
```matlab
J=roifill(I,BW)
```
其功能是：用掩模图像BW选择区域。
```matlab
[J,BW]=roifill(…)
```
其功能是：在填充区域的同时还返回掩模图像BW。
```matlab
J=roifill(x,y,I,xi,yi)
[x,y,J,BW,xi,yi]=roifill(…)
```
其功能是：在指定的坐标系X－Y下填充由向量xi,yi指定的多边形区域。

例：下面是一个为填充指定的区域程序清单：
```matlab
I=imread('rice.tif');

I=imread('rice.png');
c=[52 72 300 270 221 194];
r=[71 21 75 121 121 75];
J=roifill(I,c,r);
subplot(1,2,1);imshow(I);
subplot(1,2,2);imshow(J);
```

参考教材：
《数字图像处理及MATLAB实现》余成波编著  重庆大学出版社  TN911.73



# 图形图像文件的读取
图形图像文件操作	相关的函数
已MAT文件加载或保存矩阵数据	Load、save
加载或保存图形文件格式的图像，如BMP、TIFF等	Imread、imwrite
显示加载到MATLAB7.0中的图像	Image、imagesc
信息查询	Imfinfo、ind2rgb


## 图形图像文件的读取
主要调用格式：
```matlab
A=imread(filename,fmt)                       [X,map]=imread(filename,fmt)
[…]=imread(filename)                         […]=imread(URL, …)
[…]=imread(…,idx)  (CUR,ICO,and TIFF only)   
[…]=imread(…,idx)  (CUR,ICO,and TIFF only)
[…]=imread(…,’frames’,idx)  (GIFF only)
[…]=imread(…,ref)  (HDF only)
[…]=imread(…,’BackgroundColor’,BG)  (PNG only)
[A,map,alpha]=imread(…)  (CUR,ICO,and PNG only)
```
最基本调用格式：
```matlab
[X,map]=imread(filename,fmt)

*imread('rice.png','5');   %读取rice.png文件的第5帧图像

*RGB=imread(‘earth.jpg’);  
%将图像earth.jpg读入MATLAB7.0工作平台，读取数据矩阵为变量RGB
```

## 图形图像文件的写入与显示
1. 用imwrite来完成图形图像文件的写人操作：
基本调用格式：imwrite(X,map,filename,fmt)

```matlab
load clown                %根据MAP格式（MATLAB数据文件格式）装载图像
imwrite(X,map,'clown.jpg')   %保存为一幅包含小丑图像的JPG文件
```
2. 可用image函数显示图像，其语法格式：
```matlab
image(C)           image(x,y,C)          image(…,’PropertyName’,PropertyValue, …)
image(’PropertyName’,PropertyValue, …)     handle=image(…)
```

函数imagesc与image函数类似，但是它可以自动标度输入数据

```matlab
load clown       %根据MAP格式（MATLAB数据文件格式）装载图像
image(10,10,X)   %显示一幅小丑图像，图像的左上角坐标为（0，0）
colormap(map)   %
```
3. 高级图像显示函数imshow，其语法格式为：
```matlab
imshow(I,n)        imshow(I,[low,high])        imshow(BW)        imshow(X,map)
imshow(RGB)      imshow(…,display_option)   imshow(x,y,A, …)    imshow filename
h=imshow(…)

I=imread('rice.png')
J=filter2([1 2;-1 -2],I)  %用模板[1 2;-1 –2]对图像滤波
imshow(I)
figure,imshow(J,[])
```

# 用图像阅读器显示图像
## 图像阅读器的开关
1．在图像阅览器中显示图像：imview
```matlab
moonfig=imread('moon.tif');
imview(moonfig)

imview('moon.tif')
```
2. 指定图像的起始大小
(1) 设置Imviewinitialmaginfication属性为‘fit’，默认值为100，100％显示
(2) 在imview函数中使用Initialmagnification参数，指定值为“fit”。
```matlab
imshow(X,map,'InitialMaginfication','fit')
```
3. 关图像阅览器
直接单击窗口下的关闭按钮，
或用下面的语句关闭：imview close all


2.3.2了解图像阅读器
图像浏览器可以在分离的窗口中显示一幅图像并提供图像的大小信息、图像像素值的范围和鼠标所指位置的状态像素值。它还提供了3个其他的工具：
浏览窗口；      像素区域；      图像信息窗口

2.3.3 使用图像阅读器导航帮助
2.3.4 使用像素区域工具
2.3.5 使用图像信息工具


2.4 不同类型图像显示方法
2.4.1索引图像及其显示




