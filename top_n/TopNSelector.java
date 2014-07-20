public class TopNSelector {
	private int[] _elements;
	private int _elementNum;
	
	private final int _topN;
	
	public TopNSelector(int[] elements, int topN) {
		_elements = elements;
		_elementNum = _elements.length;
		
		_topN = topN;
	}
	
	public void build() {
		for(int i = _elementNum / 2; i < _elementNum; ++i)
			shiftUp(i);
	}
	
	public void shiftUp(int i) {
		int curr = i;
		int parent = (curr-1) / 2;
		while(curr > 0) {
			if(_elements[curr] > _elements[parent]) {
				int tmp = _elements[curr];
				_elements[curr] = _elements[parent];
				_elements[parent] = tmp;
			}
			
			curr = parent;
			parent = (curr-1) / 2;
		}
	}
	
	public int[] select() {
		int[] topNElements = new int[_topN];
		for(int i = 0; i < _topN; ++i)
			topNElements[i] = pop();
			
		return topNElements;
	}
	
	public int pop() {
		int topElement = _elements[0];
		
		_elements[0] = _elements[--_elementNum];
		shiftDown();
		
		return topElement;
	}
	
	public void shiftDown() {
		int curr = 0;
		int child = curr*2+1;
		while(child < _elementNum) {
			if((child+1 < _elementNum) && (_elements[child+1] > _elements[child]))
				++child;
			
			if(_elements[curr] > _elements[child])
				break;
			
			int tmp = _elements[curr];
			_elements[curr] = _elements[child];
			_elements[child] = tmp;
			
			curr = child;
			child = child*2+1;
		}
	}
	
	public static void main(String[] args) {
		int[] data = {31, 24, 9, 17, 21, 5, 9, 13, 36, 1, 32, 8, 46, 55, 49};
		for(int i = 0; i < data.length; ++i)
			System.out.print(data[i] + ",");
		System.out.println();
		
		TopNSelector topNSelector = new TopNSelector(data, 3);
		topNSelector.build();
		
		int[] result = topNSelector.select();
		for(int i = 0; i < result.length; ++i)
			System.out.print(result[i] + ",");
	}
}
