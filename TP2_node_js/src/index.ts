import Stack from "./structures/Stack";
import BenchDataStructure from "./BenchDataStructure";

const main = () => {
    const stack: BenchDataStructure<number> = new Stack();
    stack.insert(1);
    console.log('COUCOU');
};

main();
