#author: Parag Patel
#email: parag.patel.one@gmail.com
#implement a Max  priority queue
#will use a binary heap to implement it
#
# External Operations 
# peek() => look at the value on top of the heap
# push(x) => push x onto heap
# pop() => return and push out value at the top of the heap
#
# Internal Operations and structures
# Node stores the values also pointers to Node's children and children store pointer to the parent
# 
# push(x) will insert a new node into the end of the heap, and then will percolateup
# pop()  will return the value at the top of the heap, and remove the last node and then percolatedown
#
#
# Main Storage will be a Ruby Array
#
#
#  0  1  2  3  4  5  6  7
# [a][b][c][d][e][f][g][i]
#
# last_node -> reference to the last node ; 7 in this case
#
# getLeftChild(parent) -> will get the left child of the parent => 2*x + 1
# getRightChild(parent) -> will get the right child of the parent => 2*x + 2
# getParent(child) -> will get parent of the child => even -> (x - 1) / 2
#
# percolateup ->  will start at node x and swap values with the parent and continue until root node is reached or parent has greater value,  
# percolatedown -> start at root node and swap values with the largest child if and only if the largest child is greater than the parent, stop if 
#                  parent is greater than the greatest child or last node is reached
#
#          
 
class PQ

  def initialize()
    @data_store = []
    @last_node = -1
    @root = 0
  end

  def peek
    if @last_node == -1
      puts "Priority Queue is empty"
      return
    end
    @data_store[@root]
  end
  
  def getLeftChild(parent)    
    2*parent + 1
  end
  
  def getRightChild(parent)
     2*parent + 2
  end
  
  def getParent(child)   
      (child - 1) / 2
  end

  def swapNodeValues(left_value,right_value)
    @data_store[left_value],@data_store[right_value] = @data_store[right_value],@data_store[left_value]
    left_value
  end
  
  def percolateup
    current_node = @last_node
    parent = getParent(current_node)

    while current_node != @root and @data_store[current_node] > @data_store[parent]
      current_node = swapNodeValues(parent,current_node)
      parent = getParent(current_node)
    end

    return
  end

  def percolatedown
    current_node = @root
     while true
      left_child, right_child,prev_node  = getLeftChild(current_node), getRightChild(current_node), current_node
      
      if left_child <= @last_node and  @data_store[left_child] > @data_store[current_node]
        current_node = swapNodeValues(left_child,current_node)
      end

      if right_child <= @last_node and  @data_store[right_child] > @data_store[current_node]
        current_node = swapNodeValues(left_child,current_node)
      end

      if prev_node == current_node
        break
      end

    end
  end

 def put(x)
   @last_node += 1
   @data_store[@last_node] = x
   percolateup
 end
 
 def pop
  if @last_node == -1
    puts "Priority Queue is empty"
    return
  end
  out = @data_store[@root]
  swapNodeValues(@root,@last_node)
  @last_node -= 1
  percolatedown
  out
end


end



