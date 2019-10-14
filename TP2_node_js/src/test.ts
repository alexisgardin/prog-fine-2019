
import {AVLNil, AVLNode, AvlTree} from "./AVL/AvlTree";
import MinHeap from "./Heap/MinHeap";

function getRandomInt(max) : number{
    return Math.floor(Math.random() * Math.floor(max));
}

const main = () => {


    console.log("\n################ TEST AVL TREE ################");

    let avl : AvlTree = new AVLNil();

    for (let i = 0; i < 10000; i++) {
        avl = avl.add(i);
    }
    avl.display("  ")
    console.log("AVL COUNT : ",avl.right.count(), avl.left.count());

    for (let i = 0; i < 10000; i++) {
        avl = avl.remove(i);
    }

    console.log("\n################ TEST BINARY HEAP ################");
    try {
        let sortedList = [];
        const heap = new MinHeap();
        for (let i = 0; i <100; i++) {
            const random = getRandomInt(100);
            heap.add(random);
            sortedList.push(random);
        }
        sortedList.sort(((a, b) => a<b?-1:b<a? 1 : 0));
        //console.log(sortedList);
        for (let i = 0; i < 10000; i++) {
            const val = heap.removeRoot();
            if(val != sortedList[i]){
                throw {"state":"error","expected": sortedList[i], "actual":val}
            }
        }
        console.log("OK")
    }
    catch(e) {
        console.error(e);
    }


};

main();
