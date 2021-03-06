class Node:
    def __init__(self,data,level,fval):
        # data for matrix, level for depth, fval for heuristic
        self.data = data
        self.level = level

    def generate_child(self):
        x,y = self.find(self.data,'-')
        # direction to move
        val_list = [[x,y-1],[x,y+1],[x-1,y],[x+1,y]]
        children = []
        # generate child node
        for i in val_list:
            child = self.shuffle(self.data,x,y,i[0],i[1])
            if child is not None:
                child_node = Node(child,self.level+1,0)
                children.append(child_node)
        return children
        
    def shuffle(self,puz,x1,y1,x2,y2):
        # move -
        if x2 >= 0 and x2 < len(self.data) and y2 >= 0 and y2 < len(self.data):
            temp_puz = []
            temp_puz = self.copy(puz)
            temp = temp_puz[x2][y2]
            temp_puz[x2][y2] = temp_puz[x1][y1]
            temp_puz[x1][y1] = temp
            return temp_puz
        else:
            return None
            

    def copy(self,root):
        # duplicate node
        temp = []
        for i in root:
            t = []
            for j in i:
                t.append(j)
            temp.append(t)
        return temp    
            
    def find(self,puz,x):
        # find -
        for i in range(0,len(self.data)):
            for j in range(0,len(self.data)):
                if puz[i][j] == x:
                    return i,j


class Puzzle:
    def __init__(self,size):
        self.n = size
        # node to transverse
        self.open = []
        # node already transversed
        self.closed = []

    def accept(self):
        # input
        puz = []
        for i in range(0,self.n):
            temp = input().split(" ")
            puz.append(temp)
        return puz        

    def check(self,start,goal):

        temp = 0
        for i in range(0,self.n):
            for j in range(0,self.n):
                if start[i][j] != goal[i][j] and start[i][j] != '-':
                    temp += 1
        return temp

    def process(self):
        print("Enter the start state")
        start = self.accept()
        print("Enter the goal state")        
        goal = self.accept()

        start = Node(start,0,0)

        node_added = 0

        self.open.append(start)
        print("\n\n")
        while True:
            cur = self.open[0]
            #check if already transversed
            done = 0
            for i in self.closed:
                if(self.check(cur.data,i.data)==0):
                    done = 1
                    break
            if done == 1:
                del self.open[0] 
                continue
            # print curent node
            print("------")
            for i in cur.data:
                for j in i:
                    print(j,end=" ")
                print("")
            # reach goal
            if(self.check(cur.data,goal) == 0):
                print("=======")
                print("node added to open list :",node_added)
                print("Iterasi :",len(self.closed))
                print("Depth :",cur.level+1)
                break
            for i in cur.generate_child():
                self.open.append(i)
                node_added += 1
            self.closed.append(cur)
            del self.open[0]

print("Enter puzzle x*x size : ",end="")
pSize = int(input())
puz = Puzzle(pSize)
puz.process()
