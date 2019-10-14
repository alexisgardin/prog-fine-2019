import * as collections from './util';
import * as arrays from './arrays';

export default class Heap {
    /**
     * Array used to store the elements of the heap.
     * @type {Array.<Object>}
     * @private
     */
    private data: number[] = [];

    /**
     * Function used to compare elements.
     * @type {function(Object,Object):number}
     * @private
     */
    private compare(numb: number, numb2: number) {
        return numb > numb2 ? 1 : numb == numb2 ? 0 : -1
    }

    constructor() {
    }

    /**
     * Returns the index of the left child of the node at the given index.
     * @param {number} nodeIndex The index of the node to get the left child
     * for.
     * @return {number} The index of the left child.
     * @private
     */
    private leftChildIndex(nodeIndex: number): number {
        return (2 * nodeIndex) + 1;
    }

    /**
     * Returns the index of the right child of the node at the given index.
     * @param {number} nodeIndex The index of the node to get the right child
     * for.
     * @return {number} The index of the right child.
     * @private
     */
    private rightChildIndex(nodeIndex: number): number {
        return (2 * nodeIndex) + 2;
    }

    /**
     * Returns the index of the parent of the node at the given index.
     * @param {number} nodeIndex The index of the node to get the parent for.
     * @return {number} The index of the parent.
     * @private
     */
    private parentIndex(nodeIndex: number): number {
        return Math.floor((nodeIndex - 1) / 2);
    }

    /**
     * Returns the index of the smaller child node (if it exists).
     * @param {number} leftChild left child index.
     * @param {number} rightChild right child index.
     * @return {number} the index with the minimum value or -1 if it doesn't
     * exists.
     * @private
     */
    private minIndex(leftChild: number, rightChild: number): number {

        if (rightChild >= this.data.length) {
            if (leftChild >= this.data.length) {
                return -1;
            } else {
                return leftChild;
            }
        } else {
            if (this.compare(this.data[leftChild], this.data[rightChild]) <= 0) {
                return leftChild;
            } else {
                return rightChild;
            }
        }
    }

    /**
     * Moves the node at the given index up to its proper place in the heap.
     * @param {number} index The index of the node to move up.
     * @private
     */
    private siftUp(index: number): void {

        let parent = this.parentIndex(index);
        while (index > 0 && this.compare(this.data[parent], this.data[index]) > 0) {
            this.swap(parent, index);
            index = parent;
            parent = this.parentIndex(index);
        }
    }


    private swap(fpos: number, spos: number) {
        this.data = this.data.map(
            (element, index) =>
                index === fpos
                    ? this.data[spos]
                    : index === spos
                    ? this.data[fpos]
                    : element
        )
    }

    /**
     * Moves the node at the given index down to its proper place in the heap.
     * @param {number} nodeIndex The index of the node to move down.
     * @private
     */
    private siftDown(nodeIndex: number): void {

        //smaller child index
        let min = this.minIndex(this.leftChildIndex(nodeIndex),
            this.rightChildIndex(nodeIndex));

        while (min >= 0 && this.compare(this.data[nodeIndex],
            this.data[min]) > 0) {
            this.swap(min, nodeIndex);
            nodeIndex = min;
            min = this.minIndex(this.leftChildIndex(nodeIndex),
                this.rightChildIndex(nodeIndex));
        }
    }

    /**
     * Retrieves but does not remove the root element of this heap.
     * @return {*} The value at the root of the heap. Returns undefined if the
     * heap is empty.
     */
    peek(): number {

        if (this.data.length > 0) {
            return this.data[0];
        } else {
            return undefined;
        }
    }

    /**
     * Adds the given element into the heap.
     * @param {*} element the element.
     * @return true if the element was added or fals if it is undefined.
     */
    add(element: number): boolean {
        if (element === undefined) {
            return false;
        }
        this.data = this.data.concat(element);
        this.siftUp(this.data.length - 1);
        return true;
    }

    /**
     * Retrieves and removes the root element of this heap.
     * @return {*} The value removed from the root of the heap. Returns
     * undefined if the heap is empty.
     */
    removeRoot(): number {

        if (this.data.length > 0) {
            const obj = this.data[0];
            const temp = this.data;
            temp[0] = this.data[this.data.length - 1];
            temp.splice(this.data.length - 1, 1);
            this.data = temp;
            if (this.data.length > 0) {
                this.siftDown(0);
            }
            return obj;
        }
        return undefined;
    }

    /**
     * Returns true if this heap contains the specified element.
     * @param {Object} element element to search for.
     * @return {boolean} true if this Heap contains the specified element, false
     * otherwise.
     */
    contains(element: number): boolean {
        const equF = collections.compareToEquals(this.compare);
        return arrays.contains(this.data, element, equF);
    }

    /**
     * Returns the number of elements in this heap.
     * @return {number} the number of elements in this heap.
     */
    size(): number {
        return this.data.length;
    }

    /**
     * Checks if this heap is empty.
     * @return {boolean} true if and only if this heap contains no items; false
     * otherwise.
     */
    isEmpty(): boolean {
        return this.data.length <= 0;
    }

    /**
     * Removes all of the elements from this heap.
     */
    clear(): void {
        this.data.length = 0;
    }


}
