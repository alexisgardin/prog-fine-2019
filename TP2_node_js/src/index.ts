import Stack from "./structures/Stack";
import BenchDataStructure from "./structures/BenchDataStructure";
import {AVLNil, AVLNode, AvlTree} from "./AVL/AvlTree";

const main = () => {
    const stack: BenchDataStructure<number> = new Stack();
    stack.insert(1);
    console.log('COUCOU');

    let avl : AvlTree = new AVLNil();

    for (let i = 0; i < 100; i++) {
        avl = avl.add(i);
    }

    console.log(avl.display("  "));
    for (let i = 0; i < 100; i++) {
        avl = avl.remove(i);
    }

    console.log(avl.display("  "));
};

main();
