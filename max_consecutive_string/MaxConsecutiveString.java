import java.util.Map;
import java.util.HashMap;

public class MaxConsecutiveString {

	public static String calc(String str) {
		if(str == null || str.isEmpty())
			return null;
		
		Map<Character, Integer> map = new HashMap<Character, Integer>();
		int maxLength = -1;
		String maxString = null;
		int start = 0;
		while(start < str.length()) {			
			int end = start;
			while(end < str.length()) {
				char c = str.charAt(end);
				if(map.containsKey(c))
					break;
				else {
					map.put(c, end);
					++end;
				}
			}
			
			if((end - start) > maxLength) {
				maxLength = end-start;
				maxString = str.substring(start, end);
				System.out.println("[" + start + ", " + end + "] => " + maxString);
			}
			
			if(end == str.length())
				break;
			else {
				start = map.get(str.charAt(end))+1;
				map.clear();
			}
		}
			
		return maxString;
	}
	
	public static void main(String[] args) {
		String str = "abcdaecfgcb";
		System.out.println("max consecutive string: " + calc(str));
	}
}
