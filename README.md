# GBIF_Splitter

## 用途

将 GBIF 网站的 Occurence Data 按国家或地区划分成较小的文件，每条记录保留以下字段：
- `gbifID`：GBIF 记录编号
- `family`：科名
- `genus`：属名
- `species`：种名
- `infraspecificEpithet`：种下阶元的加词
- `taxonRank`：分类阶元等级
- `scientificName`：学名
- `countryCode`：国家代码
- `locality`：地点
- `decimalLatitude`：纬度，北纬为正，南纬为负，用十进制表示，单位为角度
- `decimalLongitude`：经度，东经为正，西经为负，用十进制表示，单位为角度
- `elevation`：海拔高度，单位为米

这些较小的文件以格式 `GBIF_ver_Kaede_*countryCode*.txt` 命名，其中 `*countryCode*` 表示记录中 `countryCode` 字段的非空值，如中国大陆的对应值为 `CN`；`countryCode` 字段空白的记录如存在，则放在文件 `GBIF_ver_Kaede_Unlabeled.txt` 中。程序同时还会生成名为 `GBIF_ver_Kaede_Report.txt` 的文件，当中保存了前述每个小文件中的记录数。

## 环境要求

Windows 10 (64x) 系统下可直接运行。要在其他系统中运行，需自行编译。

## 使用方法

1. 在 GBIF 网站上选取需要的 Occurence Data，以 CSV 格式下载；
1. 打开下载的 ZIP 文件，将包含的 CSV 文件解压到任意目录下，重命名为 `GBIF_Global.txt`；
1. 将 `GBIF_Splitter_ver_Kaede.exe` 移动到同一目录中后运行。

## 文件列表

- `GBIF_Splitter_ver_Kaede.exe`：程序文件
- `GBIF_Splitter_ver_Kaede_readme.pdf`：使用说明（即本文件）
- `GBIF_Global.txt`：样例输入，此处为 GBIF 网站上 *Euptelea* 属的 Occurence Data
