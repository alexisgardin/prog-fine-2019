class ListNode {

    value: number;

    left: ListNode;
    right: ListNode;

    constructor(value: number) {
        this.value = value;
        this.left = undefined;
        this.right = undefined;
    }
}


export class List {

    root: ListNode = undefined;

    constructor() {
    }

    toBinaryString(v: number): string {
        return (v >>> 0).toString(2);
    }

    getNode = (index: number): ListNode => {
        let node = this.root;
        const str = this.toBinaryString(index);
        for (let i = 1; i < str.length; i++) {
            const cur = str.charAt(i);

            if (cur === '1') {
                if (!node.right) {
                    node.right = new ListNode(-1);
                }
                node = node.right;
            } else {
                if (!node.left) {
                    node.left = new ListNode( -1);
                }
                node = node.left;
            }
        }

        return node;
    };

    set = (index: number, value: number): List => {
        if (index === 0 && this.root === undefined) {
            this.root = new ListNode(value);
            return this;
        } else if (this.root === undefined) {
            this.root = new ListNode(-1);
        }

        let node = this.getNode(index);
        node.value = value;

        return this;
    };

    get = (index: number): number => {
        if (index === 0) {
            return this.root.value;
        }

        return this.getNode(index).value;
    }
}
