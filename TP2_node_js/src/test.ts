
import {AVLNil, AVLNode, AvlTree} from "./structures/custom/AVL/AvlTree";
import MinHeap from "./structures/custom/Heap/MinHeap";

function getRandomInt(max) : number{
    return Math.floor(Math.random() * Math.floor(max));
}

const main = () => {


    console.log("\n################ TEST AVL TREE ################");
    try {
        for (let i = 0; i < 100; i++) {
            let avl : AvlTree = new AVLNil();

            for (let j = 0; j < getRandomInt(100); j++) {
                avl = avl.add(j);
            }
            let result = avl.diff();
            if(result!== 0 && result!==-1)
                throw {"state":"error","expected": '0 or -1', "actual":result}
        }


        let avl : AvlTree = new AVLNil();
        for (let j = 0; j < 100; j++) {
            avl = avl.add(j);
        }
        for (let i = 0; i < 100; i++) {
            avl = avl.remove(i);
        }
        if(!("$\n"==avl.display(""))) //If the print function are empty then we have nothing to print so all data are remove
        {
            throw {"state":"error","expected": 'EMPTY AVL'}
        }

        avl  = new AVLNil();
        for (let j = 0; j < 100; j++) {
            const test= getRandomInt(100);
            avl = avl.add(test);
            if(avl.find(test) === null){
                throw {"state":"error","expected": 'ERROR IN FIND'}
            }
        }

        if(avl.find(100000) !== null){
            throw {"state":"error","expected": 'HE FOUND SOMETHING THAT DOESNT EXIST'}
        }
        console.log("OK")
    }catch (e) {
        console.log(e)
    }



    console.log("\n################ TEST BINARY HEAP ################");
    try {
        let sortedList = [];
        const heap = new MinHeap();
        for (let i = 0; i <100000; i++) {
            const random = getRandomInt(100);
            heap.add(random);
            sortedList.push(random);
        }
        sortedList.sort(((a, b) => a<b?-1:b<a? 1 : 0));
        //console.log(sortedList);
        for (let i = 0; i < 100000; i++) {
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
