# 1A2B益智遊戲
**作者:413410037 王佑伊**

此程式可讓玩家與電腦進行1A2B益智遊戲

# 程式流程圖
![image](https://github.com/abbywang123/413410037/blob/main/%E6%8F%90%E7%A4%BA%E7%8E%A9%E5%AE%B6%E6%98%AF%E5%90%A6%E7%82%BA%E8%A9%B2%E7%8E%A9%E5%AE%B6.png)

# 使用說明
1.玩家選擇是否要重新開始新一輪的遊戲

2.玩家輸入自己的姓名

3.玩家輸入自己預期幾秒鐘可以結束遊戲

4.玩家選擇要進行 A.猜題者模式 B.出題者模式

5.**A.猜題者模式**

        1.自己在心中產生一組四位數字(五秒思考時間)
        
        2.電腦產生一組數字
        
        3.輸入此組數字是幾A幾B
        
        4.不斷重複步驟2~3，直到電腦贏或是時間已經到
        
  **B.出題者模式**
  
        1.輸入一組四位數字
        
        2.電腦給予玩家幾A幾B
        
        3.不斷重複步驟1~2直到玩家猜對或是時間已經到
        
6.顯示分數及排名

7.玩家可選擇是再玩一次，是的話，程式重新回到步驟3

# 程式模組
1.儲存玩家資料

![image](https://github.com/abbywang123/413410037/blob/main/saveplayers.png)

2.讀取玩家資料

![image](https://github.com/abbywang123/413410037/blob/main/loadplayers.png)

3.重置玩家資料

![image](https://github.com/abbywang123/413410037/blob/main/resetplayers.png)

4.查找玩家資料:比對名稱是否有相同

![image](https://github.com/abbywang123/413410037/blob/main/fiindplayer.png)

5.輸出和計算玩家排名

![image](https://github.com/abbywang123/413410037/blob/main/playerranking.png)

6.生成電腦猜測的候選組合

![image](https://github.com/abbywang123/413410037/blob/main/generateguess.png)

7.計算A和B的數量

![image](https://github.com/abbywang123/413410037/blob/main/calculate.png)

8.隨機產生四位數字

![image](https://github.com/abbywang123/413410037/blob/main/generatedigits.png)

9.檢查輸入數字是否合理

![image](https://github.com/abbywang123/413410037/blob/main/check.png)

# 程式新增的功能
1.**功能一**:
玩家可以自己選擇要進行的遊戲時間，如果玩家時間超出自己選擇的遊戲時間，則顯示遊戲結束

2.**功能二**:計算遊戲分數

  (1)模式A:如果你設定的數字，可以使電腦在15步內成功解出，則分數為150分，之後電腦每少一步，分數即少10分，
  若電腦無法在15步內解出，則分數顯示-10分，若是玩家時間超出自己選擇的限制時間，則分數會倒扣20分。
      
  (2)模式B:如果你能在第一步就將數字成功猜出，則分數為150分，第二步145分，之後每一步即扣10分。
  若是玩家時間超出自己選擇的限制時間，則分數會倒扣20分。
      
3.**功能三**:玩家排名系統，一開始先給玩家輸入名稱，若排名系統中已有這個玩家名稱，則詢問玩家排名系統上已有此玩家名字，確定是否是本人。若是答案是是的話，則分數進行更新，若是不是的話，則要求玩家輸入新名稱，在開始遊戲。

4.**功能四**:選擇是否重新開始新的一輪排名，如果選擇是的話，則所有玩家遊戲資料清除，重新開始。

5.**功能五**:在模式A中，新增五秒時間，給玩家思考四位數字

# 程式運行畫面截圖
![image](https://github.com/abbywang123/413410037/blob/main/01.png)

![image](https://github.com/abbywang123/413410037/blob/main/02.png)

![image](https://github.com/abbywang123/413410037/blob/main/03.png)

![image](https://github.com/abbywang123/413410037/blob/main/04.png)

![image](https://github.com/abbywang123/413410037/blob/main/05.png)

