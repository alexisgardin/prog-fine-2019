import Stack from "./structures/Stack";
import BenchDataStructure from "./structures/BenchDataStructure";

const main = () => {
    const stack: BenchDataStructure<number> = new Stack();
    stack.insert(1);
    console.log('COUCOU');
};

main();
