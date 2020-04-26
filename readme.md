# 代码的环境配置
**打开项目属性-->VC++目录-->包含目录，增加下面三个个路径：** 
- D:\itpp\itpp-4.3.1
- D:\sigpack\sigpack127\sigpack
- D:\sigpack\armadillo9\include\

**属性-->VC++目录-->库目录，增加下面三个个路径：**
- D:\itpp\itpp-4.3.1\lib
- D:\sigpack\armadillo9\lib
**属性-->链接器-->附加库目录:**
- D:\itpp\itpp-4.3.1\lib
- D:\sigpack\armadillo9\lib
**属性-->链接器-->附加依赖项:**
- itpp_debug_win32.lib
- itpp_debug_win32.lib
- blas_win32_MTd.lib
- lapack_win32_MTd.lib
