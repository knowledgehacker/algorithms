import java.util.List;
import java.util.ArrayList;
import java.util.Map;
import java.util.HashMap;

public class TrieTree {
	private final int _alphabetSize;
	private final Map<Character, Integer>_letter2Index;

	private final TriesNode _root;
	private final List<String> _words;
	private int _wordNum;
	// for debug use
	private final Map<String, Integer> _word2Index;
	
	public TrieTree(char[] alphabet, String[] words) {
		_alphabetSize = alphabet.length;
		
		_letter2Index = new HashMap<Character, Integer>();
		for(int i = 0; i < _alphabetSize; ++i)
			_letter2Index.put(alphabet[i], i);
		
		_root = new TriesNode();
		_words = new ArrayList<String>();
		_wordNum = 0;
		// for debug use
		_word2Index = new HashMap<String, Integer>();
		for(String word: words)
			put(word);
	}
	
	public void put(String word) {
		TriesNode node = _root;
		int wordLength = word.length();
		int i = 0;
		while(i < wordLength) {
			char value = word.charAt(i);
			TriesNode[] nodeLinks = node.getLinks();
			int j = 0;
			while(j < _alphabetSize) {
				TriesNode link = nodeLinks[j];
				if(link != null && link.getValue() == value)
					break;
				++j;
			}
			if(j == _alphabetSize)
				break;
				
			node = nodeLinks[j];
			++i;
		}
		
		if(i == wordLength) {
			if(node.getWordIndex() == -1) {
				node.setWordIndex(++_wordNum);
				_words.add(word);
				// for debug use
				_word2Index.put(word, _wordNum);
			}
			return;
		}
			
		// node and i
		TriesNode parent = node;
		char value = 'X';
		TriesNode curr = null;
		for(int k = i; k < wordLength-1; ++k) {
			value = word.charAt(k);
			curr = new TriesNode();
			curr.setValue(value);
			parent.setLink(_letter2Index.get(value), curr);
				
			parent = curr;
		}
		value = word.charAt(wordLength-1);
		curr = new TriesNode();
		curr.setValue(value);
		curr.setWordIndex(_wordNum++);
		parent.setLink(_letter2Index.get(value), curr);
		_words.add(word);
		// for debug use
		_word2Index.put(word, _wordNum);
	}
	
	public int get(String word) {
		TriesNode node = _root;
		int wordLength = word.length();
		int i = 0;
		while(i < wordLength) {
			char value = word.charAt(i);
			TriesNode[] nodeLinks = node.getLinks();
			int j = 0;
			while(j < _alphabetSize) {
				TriesNode link = nodeLinks[j];
				if(link != null && link.getValue() == value)
					break;
				++j;
			}
			if(j == _alphabetSize)
				break;
			
			node = nodeLinks[j];
			++i;
		}
		
		if(i == wordLength)
			return node.getWordIndex();
		
		return -1;
	}
	
	public void debug() {
		
	}
	
	private class TriesNode {
		private char _value;
		private int _word_index;
		private final TriesNode[] _links;
		
		public TriesNode() {
			_value = 'X';
			_word_index = -1;
			
			_links = new TriesNode[_alphabetSize];
		}
		
		public final void setValue(char value) {
			_value = value;
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
		
		public final void setLink(int idx, TriesNode link) {
			_links[idx] = link;
		}
		
		public final TriesNode[] getLinks() {
			return _links;
		}
	}

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		char[] alphabet = {'a', 'b', 'c', 'd', 'e', 'f', 'g',
			'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q',
			'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'
		};
		
		String[] words = {"she", "sells", "sea", "shells", "by", "the", "sea", "shore"};
		TrieTree tt = new TrieTree(alphabet, words);
		String word = "shells";
		int wordIndex = tt.get(word);
		System.out.println("word: " + word + ", wordIndex: " + wordIndex);
	}
}
