<!--
 * @Author: Anxjing.AI
 * @Date: 2020-09-10 01:54:28
 * @LastEditTime: 2020-09-10 06:22:23
 * @LastEditors: Anajing.AI
 * @Description: 
 * @FilePath: \Anxjing.AI\JingNotebook\tool\git添加邮箱和账户.md
 * @THIS FILE IS PART OF Anxjing.AI PROJECT
-->
# git配置账号(用户名/邮箱)

## 配置账号的目的
作为代码提交、下拉、注释时的记录。配置信息存在于文件`.gitconfig`中；

## 配置用户名
```powershell
git config --global user.name "username"
```

## 配置邮箱
```powershell
git config --global user.email useremail@ai.com 
```

## 查看配置信息
```
git config --list
```

## 配置邮箱
```powershell
git config user.name 
或者
git config user.email
```

## git config参数

```powershell
$ git config -help
```

```bash
usage: git config [<options>]

Config file location
    --global              use global config file
    --system              use system config file
    --local               use repository config file
    --worktree            use per-worktree config file
    -f, --file <file>     use given config file
    --blob <blob-id>      read config from given blob object

Action
    --get                 get value: name [value-regex]
    --get-all             get all values: key [value-regex]
    --get-regexp          get values for regexp: name-regex [value-regex]
    --get-urlmatch        get value specific for the URL: section[.var] URL
    --replace-all         replace all matching variables: name value [value_regex]
    --add                 add a new variable: name value
    --unset               remove a variable: name [value-regex]
    --unset-all           remove all matches: name [value-regex]
    --rename-section      rename section: old-name new-name
    --remove-section      remove a section: name
    -l, --list            list all
    -e, --edit            open an editor
    --get-color           find the color configured: slot [default]
    --get-colorbool       find the color setting: slot [stdout-is-tty]

Type
    -t, --type <>         value is given this type
    --bool                value is "true" or "false"
    --int                 value is decimal number
    --bool-or-int         value is --bool or --int
    --path                value is a path (file or directory name)
    --expiry-date         value is an expiry date

Other
    -z, --null            terminate values with NUL byte
    --name-only           show variable names only
    --includes            respect include directives on lookup
    --show-origin         show origin of config (file, standard input, blob, command line)
    --default <value>     with --get, use default value when missing entry

```

## git记住密码(避免每次提交代码都要重新输出)
```bash
git config --global credential.helper store

/*
在.gitconfig中生成一下配置
[credential]
	helper = store
*/
```

## ssh-keygen生成公钥
```bash
ssh-keygen -t rsa -C "email@ai.com"
```

![](https://gitee.com/Anxjing_AI/AnImg/raw/master/img/20200910062134.png)
