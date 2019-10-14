
import {AVLNil, AVLNode, AvlTree} from "./AVL/AvlTree";
import MinHeap from "./Heap/MinHeap";

function getRandomInt(max) {
    return Math.floor(Math.random() * Math.floor(max));
}

const main = () => {
    console.log('COUCOU');

    let avl : AvlTree = new AVLNil();

    for (let i = 0; i < 100; i++) {
       avl = avl.add(i);
    }
    console.log( avl.index(5));
    console.log("Size : ", avl.count())
    for (let i = 0; i < 100; i++) {
        avl = avl.remove(i);
    }

    const heap = new MinHeap();
    for (let i = 0; i <10; i++) {

        heap.add(getRandomInt(100));
    }
   console.log(heap);
    console.log(heap.removeRoot());

};

main();
