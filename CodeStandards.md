## Welcome to join our InvincibleAutoChess Project

### Naming Notations

#### File Name & Class Name
the two item use the same naming notation,here are the examples
```C++
PlayScene.h
PlayScene.cpp
CloseButtonItem.png
class PlayScene : public Scene
```

#### Variable Name & Function Name
the two item use the same naming notation,here are the examples
```C++
auto visibleSize = Director::getInstance()->getVisibleSize();
virtual void applicationWillEnterForeground();
// pay attention to the first lowercase letter
```

### File Annotation
- We should use file annotations to modify the file basic attributes in ".h" files
- Here is the example:(the items in this example can be changed/added)
- You can also use English-styled annotations
```C++
/********************************************
 * 功能：游戏逻辑控制器
 * 作者：2053300-胡锦晖
 * 版本：1.0.0
 * 游戏引擎：Cocos2d-x 3.17.2
 * ******************************************
 * 说明：本游戏图片资源均来自网络，内容仅用于
 * 完成特色测评项目，不具有传播性质
 ********************************************/
```

### Function Annotation
- we usually use single-line comment to modify the attributes of a function in the class declaration
```C++
public:
// what's the attributes of the function
bool TestFunction(int a, int b);
```
- if the function is kind of complex, we can also use multiline comments
```C++
/********************************************
 * name
 * attributes
 * return
 * parameters
 ********************************************/
```

### Code Tips
- Cocos prefer to use key word `auto` to identify a variable.

### Please Add Other Questions of Coding in this File!