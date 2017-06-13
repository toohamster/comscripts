package cn.amlove.csvparse;

import java.util.ArrayList;
import java.util.Map;

public class Data {

	private String path;

	public String getPath() {
		return path;
	}

	public void setPath(String path) {
		this.path = path;
	}

	private Map<String, Integer> headers;
	private ArrayList<Map<String, String>> rows;

	public Map<String, Integer> getHeaders() {
		return headers;
	}

	public void setHeaders(Map<String, Integer> headers) {
		this.headers = headers;
	}

	public ArrayList<Map<String, String>> getRows() {
		return rows;
	}

	public void setRows(ArrayList<Map<String, String>> rows) {
		this.rows = rows;
	}

}
