# PHP 扩展开发

[ext_skel 脚本]

PHP 扩展由几个文件组成，这些文件对所有扩展来说都是通用的。不同扩展之间，这些文件的很多细节是相似的，只是要费力去复制每个文件的内容。幸运的是，有脚本可以做所有的初始化工作，名为 ext_skel，自 PHP 4.0 起与其一起分发。

不带参数运行 ext_skel 在 PHP 5.2.2 中会产生以下输出：

php-5.2.2/ext$ ./ext_skel 
./ext_skel --extname=module [--proto=file] [--stubs=file] [--xml[=file]]
           [--skel=dir] [--full-xml] [--no-help]

  --extname=module   module is the name of your extension
  --proto=file       file contains prototypes of functions to create
  --stubs=file       generate only function stubs in file
  --xml              generate xml documentation to be added to phpdoc-cvs
  --skel=dir         path to the skeleton directory
  --full-xml         generate xml documentation for a self-contained extension
                     (not yet implemented)
  --no-help          don't try to be nice and create comments in the code
                     and helper functions to test if the module compiled
通常来说，开发一个新扩展时，仅需关注的参数是 --extname 和 --no-help。除非已经熟悉扩展的结构，不要想去使用 --no-help; 指定此参数会造成 ext_skel 不会在生成的文件里省略很多有用的注释。
剩下的 --extname 会将扩展的名称传给 ext_skel。"name" 是一个全为小写字母的标识符，仅包含字母和下划线，在 PHP 发行包的 ext/ 文件夹下是唯一的。

--proto 选项允许开发人员指定一个头文件，由此创建一系列 PHP 函数，表面上看就是要开发基于一个函数库的扩展，但对大多数头现代的文件来说很少能起作用。如果用 zlib.h 头文件来做测试，就会导致在 ext_skel 的输出文件中存在大量的空的和无意义的原型文件。--xml 和 --full-xml 选项当前完全不起作用。--skel 选项可用于指定用一套修改过的框架文件来工作，这是本节范围之外的话题了。

[构建实例]

[kenxu@10-9-47-178 php-learn]$ ext_skel --extname=toohamster --skel=/home/kenxu/source/php-5.4.40/ext/skeleton
Creating directory toohamster
Creating basic files: config.m4 config.w32 .svnignore toohamster.c php_toohamster.h CREDITS EXPERIMENTAL tests/001.phpt toohamster.php [done].

To use your new extension, you will have to execute the following steps:

1.  $ cd ..
2.  $ vi ext/toohamster/config.m4
3.  $ ./buildconf
4.  $ ./configure --[with|enable]-toohamster
5.  $ make
6.  $ ./sapi/cli/php -f ext/toohamster/toohamster.php
7.  $ vi ext/toohamster/toohamster.c
8.  $ make

Repeat steps 3-6 until you are satisfied with ext/toohamster/config.m4 and
step 6 confirms that your module is compiled into PHP. Then, start writing
code and repeat the last two steps as often as necessary.

编辑 config.m4 文件,将 第 10,11,12行前面的dnl 移除,然后 编译才能生成 .so文件
编译时应该使用参数 

./configure --with-php-config=/usr/local/bin/php-config
make
编译完之后,在 modules目录下就会产生 toohamster.so , toohamster.la 文件

