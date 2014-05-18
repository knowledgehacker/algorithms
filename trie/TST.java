import java.util.List;
import java.util.ArrayList;
import java.util.Map;
import java.util.HashMap;

public class TST {
	private final List<TSTNode> _root;
	
	private int _wordIndex;
	private final Map<String, Integer> _word2Index;
	
	public TST(String[] words) {
		_root = new ArrayList<TSTNode>();
		
		_wordIndex = 0;
		_word2Index = new HashMap<String, Integer>();
		for(String word: words)
			put(word);
	}
	
	private class MatchInfo {
		private final int _idx;
		private final TSTNode _node;
		
		public MatchInfo(int idx, TSTNode node) {
			_idx = idx;
			_node = node;
		}
		
		public final int getIdx() {
			return _idx;
		}
		
		public final TSTNode getNode() {
			return _node;
		}
	}
	
	private final MatchInfo match(String word) {
		char firstChar = word.charAt(0);
		int tstNum = _root.size();
		if(tstNum == 0)
			return new MatchInfo(0, null);
		
		int idx = 0;
		TSTNode tst = null;
		while(idx < tstNum) {
			tst = _root.get(idx);
			if(tst.getValue() == firstChar)
				break;
			++idx;
		}
		if(idx == tstNum)
			return new MatchInfo(0, null);
		
		TSTNode node = tst.getMiddleLink();
		int wordLength = word.length();
		int i = 1;
		while(i < wordLength) {
			char value = word.charAt(i);
			if(value < node.getValue()) {
				if(node.getLeftLink() == null)
					break;
				node = node.getLeftLink();
			} else if(value == node.getValue()) {
				++i;
				
				if(node.getMiddleLink() == null)
					break;
				node = node.getMiddleLink();
			} else {
				if(node.getRightLink() == null)
					break;
				node = node.getRightLink();
			}
		}
		
		return new MatchInfo(i, node);
	}
	
	public final boolean exists(String word) {
		if(word.isEmpty())
			return false;
		
		MatchInfo matchInfo = match(word);
		int i = matchInfo.getIdx();
		TSTNode node = matchInfo.getNode();
		if(i == 0 && node == null)
			return false;
		
		if(i == word.length() && node.getWordIndex() != -1)
			return true;
		
		return false;
	}
	
	public int get(String word) {
		MatchInfo matchInfo = match(word);
		int i = matchInfo.getIdx();
		TSTNode node = matchInfo.getNode();
		if(i == word.length())
			return node.getWordIndex();
		
		return -1;
	}
	
	public void put(String word) {
		MatchInfo matchInfo = match(word);
		int i = matchInfo.getIdx();
		TSTNode node = matchInfo.getNode();
		if(i == 0 && node == null) {
			_root.add(createSubTST(word, 0));
			return;
		}
		
		/*
		 * If "word" is a prefix of a word terminated at node "node" in the ternary search tree.
		 * case 1: "word" doesn't match the word terminated at node "node",
		 * set the word index of the node "node", and increase the word index.
		 * case 2: "word" matches the word terminated at node "node", nothing has to do.
		 */
		if(i == word.length()) {
			if(node.getWordIndex() == -1) {
				node.setWordIndex(_wordIndex);
				_word2Index.put(word, _wordIndex++);
			}
			
			return;
		}
		
		/*
		 * If "word" is not a prefix of a word in the ternary search tree,
		 * and matching "word" stops at ith character of "word" and node "node" for the following conditions:
		 * case 1: word.charAt(i) == node.getValue(), but node.getMiddleLink() == null.
		 * Create a sub ternary search trie for the remaining characters begging from index 'i+1' of "word",
		 * and let node's middle link point to it.
		 * case 2 & 3: word.charAt(i) </> node.getValue(), but node.getLeft/RightLink() == null.
		 * , 
		 * Create a sub ternary search trie for the remaining characters begging from index 'i' of "word",
		 * if node.getWordIndex() != -1 && node.getMiddleLink() == null, let 'node''s middle link point to it,
		 * otherwise, let 'node''s left/right link point to it.
		 */
		char nodeValue = node.getValue();
		char currCharValue = word.charAt(i);
		if(currCharValue == nodeValue) {
			node.setMiddleLink(createSubTST(word, i+1));
		} else {
			if(node.getWordIndex() != -1 && node.getMiddleLink() == null)
				node.setMiddleLink(createSubTST(word, i));
			else {
				if(currCharValue < nodeValue)
					node.setLeftLink(createSubTST(word, i));
				else
					node.setRightLink(createSubTST(word, i));
			}
		}
	}
	
	private final TSTNode createSubTST(String word, int start) {
		TSTNode root = new TSTNode(word.charAt(start));
		if(start == word.length()-1) {
			root.setWordIndex(_wordIndex);
			_word2Index.put(word, _wordIndex++);
			
			return root;
		}
		
		int i = start+1;
		TSTNode node = root;
		TSTNode link = null;
		while(i < word.length()-1) {
			link = new TSTNode(word.charAt(i));
			node.setMiddleLink(link);
			
			node = link;
			++i;
		}
		link = new TSTNode(word.charAt(i));
		link.setWordIndex(_wordIndex);
		_word2Index.put(word, _wordIndex++);
		node.setMiddleLink(link);
		
		return root;
	}
	
	private class TSTNode {
		private char _value;
		private int _word_index;
		private TSTNode _left, _middle, _right;
		
		public TSTNode(char value) {
			_value = value;
			_word_index = -1;
		}
		
		public final char getValue() {
			return _value;
		}
		
		public final void setWordIndex(int word_index) {
			_word_index = word_index;
		}
		
		public final int getWordIndex() {
			return _word_index;
		}
		
		public final void setLeftLink(TSTNode left) {
			_left = left;
		}
		
		public final TSTNode getLeftLink() {
			return _left;
		}
		
		public final void setMiddleLink(TSTNode middle) {
			_middle = middle;
		}
		
		public final TSTNode getMiddleLink() {
			return _middle;
		}
		
		public final void setRightLink(TSTNode right) {
			_right = right;
		}
		
		public final TSTNode getRightLink() {
			return _right;
		}
	}

	public static void main(String[] args) {
		String[] words = {"she", "sells", "sea", "shells", "by", "the", "sea", "shore"};
		TST tst = new TST(words);
		String word = "shells";
		int wordIndex = tst.get(word);
		System.out.println("word: " + word + ", wordIndex: " + wordIndex);
	}

}
