import BenchDataStructure from "../structures/BenchDataStructure";
import Timer from "./Timer";
import {generateRandomList, shuffle} from "./Generator";
import {BenchmarkResult, Result} from "./Result";

const ITERATIONS = 10000;
let values = generateRandomList(ITERATIONS, ITERATIONS);

const indexes = shuffle(Array.from({length: ITERATIONS}, (x, i) => i));

const avg = (tab: number[]) => tab.reduce((previous, current) => current += previous) / tab.length;

class Benchmark {

    ds: BenchDataStructure<number>;

    constructor(dataStructure: BenchDataStructure<number>) {
        this.ds = dataStructure;
    }

    avgBenchmark(iterationsCount: number, callback: (i: number) => void): number[] {
        const timer = new Timer();
        const times: number[] = [];

        for (let i = 0; i < iterationsCount; i++) {
            timer.start();
            callback(i);
            times.push(timer.stopAndGet());
        }

        return times;
    }

    benchInsertion(ds: BenchDataStructure<number>): Result {
        console.log(`--------> INSERTION: ${ds.name}`);
        const times = this.avgBenchmark(ITERATIONS, i => ds.insert(values[i]));
        return {times, avgTime: avg(times)};
    }

    benchSearch(ds: BenchDataStructure<number>): Result {
        console.log(`--------> SEARCH: ${ds.name}`);
        if (ds.name === "AVL") { // Voir pour chercher des valeurs qui ne sont pas dans l'AVL
            values = shuffle(values);
        }

        const times = this.avgBenchmark(ITERATIONS, i => ds.search(values[i]));
        return {times, avgTime: avg(times)};
    }

    benchDeletion(ds: BenchDataStructure<number>): Result {
        console.log(`--------> DELETION: ${ds.name}`);
        const times = this.avgBenchmark(ITERATIONS, i => ds.name === "AVL" ? ds.pop(values[i]) : ds.name === "ARRAY" ? ds.pop(indexes[i]) : ds.pop());
        return {times, avgTime: avg(times)};
    }

    runAll(): BenchmarkResult {
        return {
            insertion: this.ds.insert ? this.benchInsertion(this.ds) : null,
            search: this.ds.search ? this.benchSearch(this.ds) : null,
            pop: this.ds.pop ? this.benchDeletion(this.ds) : null
        };
    }
}

export default Benchmark;
