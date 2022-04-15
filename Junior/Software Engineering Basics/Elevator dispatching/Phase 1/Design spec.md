# Design Spec

## 设计思路

* 用多线程的方式模拟电梯的运行。
* 调度的参与方分为控制终端、电梯、乘客三部分。
* 控制终端：监视各楼层等待乘梯的乘客，保存各楼层乘客的信息。
* 电梯：由控制终端启动，自动根据设定运行。到达某一楼层后，到达目的地的乘客自行下梯，然后电梯向控制终端请求当前楼层等待的乘客信息，让需要乘坐的乘客进入电梯。
* 乘客：乘客实体，包含目标楼层和体重。

## 类定义

1. **Passenger**
  * Variables
    | Variable     | Type | Comment  |
    | -------- | ---- | -------- |
    | *weight* | int  | 乘客体重 |
    | *dest*   | int  | 目标楼层 |

  * Methods
    | Method    | Parameters | Return type | Comment |
    | --------- | ---------- | ----------- | ------- |
    | *getWeight* |            | int         |返回乘客体重        |
    | *getDest* |            | int         |  返回目标楼层       |

2. **Control**
  * Variables
    | Variable      | Type                          | Comment        |
    | ------------- | ----------------------------- | -------------- |
    | *waitingUp*   | List\<LinkedList\<Passenger>> | 等待上楼的乘客 |
    | *waitingDown* | List\<LinkedList\<Passenger>> | 等待下楼的乘客 |
    | *elevator*    | Elevator[]                    | 运行的电梯对象 |

  * Methods
    | Method            | Parameters                               | Return type | Comment                                |
    | ----------------- | ---------------------------------------- | ----------- | -------------------------------------- |
    | *add*             | int floor, Passenger passenger           | boolean     | 添加新来的乘客                         |
    | *isEmpty*         | int floor, boolean up                    | boolean     | 查看某一楼层是否有等待的乘客           |
    | *get*             | int floor, boolean up                    | Passenger   | 获取某一楼层下一个等待上楼或下楼的乘客 |
    | *remove*          | int floor, boolean up                    | void        | 乘客进入电梯，移除从等待列表中移除     |
    | *setServedFloors* | int elevator, Set\<Integer> servedFloors | void        | 设置某台电梯的服务楼层                 |
    | *setMaxWeight*    | int elevator, int maxWeight              | boolean     | 设置某台电梯的最大载重                 |
    | *setMaxCapacity*  | int elevator, int maxCapacity            | boolean     | 设置某台电梯的最大容量                 |
    | *setMoveSpeed*    | int elevator, int moveSpeed              | boolean     | 设置某台电梯的移动速度                 |
    | *setDoorSpeed*    | int elevator, int doorSpeed              | boolean     | 设置某台电梯的开关门速度               |
    | *setInitialFloor* | int elevator, int floor                  | boolean     | 初始化某台电梯所在楼层                 |
    | *getCurrentFloor* | int elevator                             | int         | 获取某台电梯当前所在楼层               |
    | *run*             | int elevator                             | void        | 启动某台电梯                           |
    
3. **Elevator**
  * Variables
    | Variable     | Type | Comment  |
    | -------- | ---- | -------- |
    | *control* | Control | 控制器对象 |
    | *up* | boolean | 指示电梯运行方向，true表示上行，false表示下行 |
    | *maxWeight* | int | 电梯最大载重 |
    | *maxCapacity* | int | 电梯最大容量 |
    | *moveSpeed* | int | 电梯移动速度 |
    | *doorSpeed* | int | 电梯开关门速度 |
    | *currentCount*  | int                   | 当前电梯内人数                                    |
    | *currentWeight* | int | 当前电梯载重 |
    | *currentFloor* | int | 当前电梯所在楼层 |
    | *servedFloors*  | List\<Integer>        | 电梯服务楼层                                      |
    | *weight* | Map<Integer, Integer> | key为楼层，value为电梯内前往key楼层的乘客体重之和 |
    | *count* | Map<Integer, Integer> | key为楼层，value为电梯内前往key楼层的乘客数量 |

  * Methods
    | Method            | Parameters                 | Return type | Comment                               |
    | ----------------- | -------------------------- | ----------- | ------------------------------------- |
    | *setMaxWeight*    | int maxWeight              | boolean     | 设置电梯的最大载重                    |
    | *setMaxCapacity*  | int maxCapacity            | boolean     | 设置电梯的最大容量                    |
    | *setMoveSpeed*    | int moveSpeed              | boolean     | 设置电梯的移动速度                    |
    | *setDoorSpeed*    | int doorSpeed              | boolean     | 设置电梯的开关门速度                  |
    | *setInitialFloor* | int floor                  | boolean     | 初始化电梯所在楼层                    |
    | *setServedFloors* | Set\<Integer> servedFloors | void        | 设置电梯的服务楼层                    |
    | *getCurrentFloor* |                            | int         | 获取电梯当前所在楼层                  |
    | *run*             |                            | void        | 电梯运行函数，实现Runnable类的run函数 |