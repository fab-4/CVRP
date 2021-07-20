# CVRP
Flowchart.jpg
The capacitated vehicle routing problem (CVRP) is a constrained version of the standard NP-Complete problem VRP in which vehicles with limited carrying capacity need to pick up or deliver items at various locations. The items have a quantity, such as weight or volume, and the vehicles have a maximum capacity that they can carry. The problem is to pick up or deliver the items for the least cost, while never exceeding the capacity of the vehicles. In this project a wholesaler is delivering the manufactured goods it sells to various retailers demanding a certain quantity of it.

We provide an approx. optimal solution to this problem using Graphs, updated Priority Queues with the help of Dijkstra's Shortest Path Algorithm.

This project was made by Priyal Jain, Ritik Jain, Saloni Ranka and Sanyam Jain in July 2020 in cpp programming language.

Contribution by Saloni Ranka and Sanyam Jain:

The main contribution by our side was the algorithm to decide which retailer should receive the next delivery. First we calculated the shortest distance (using dijkstra algorithm) of every retailer (with their respective parent node) the wholesaler sells the product to. With the help of an updated priority queue(Heap), we found the farthest retailer asking for the delivery. Btrack function helped in identifying whether there are retailers on the path which can be delivered to other than the farthest retailer. We used a stack and a queue to maintain the order of delivery for each carrier. If the carrier is still capable of delivering to some retailers, the most suitable retailer would be the one whose sum of shortest distance from the wholesaler and the current retailer is minimum. The process will continue for every retailer delivered till the point either the carrier becomes empty or there are no feasible deliveries resulting into the returning of the carrier to the wholesaler. If the carrier returns to the wholesaler and still delivery to some retailer is left then another carrier is dispatched following the same process for remaining deliveries.


Contribution by Priyal Jain and Ritik Jain: 

The main contribution by our side was to create an updated structure of priority queue by modifying heap with pairs which also helps for deleting an element from any position. A Heap must also satisfy the heap-order property, the value stored at each node is greater than or equal to its children, of max heap. We made some of its standard functions like push, pop, getMaximum and isEmpty with slight modifications. If some element in it is violating some property of the Heap then the PercolateDown function is used to restore that property. Heapify is the process of converting an array of elements into a Heap. 


Contributors :  

Priyal Jain         https://www.linkedin.com/in/priyal-jain-5b4ba616a/ 

Ritik Jain          https://www.linkedin.com/in/ritik-jain-8092b6185/ 

Saloni Ranka        https://www.linkedin.com/in/saloni-ranka-9837ba173/ 

Sanyam Jain         https://www.linkedin.com/in/sanyam-jain-197901183/
