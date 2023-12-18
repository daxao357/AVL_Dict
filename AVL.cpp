#include "AVL.hpp"
#include <algorithm>
#include <cctype>
#include <cmath>
#include <fstream>
#include <limits>
#include <stack>


int AVL::size(const std::shared_ptr<Vertex>& p) {
	int s = 0;
	if (p == NULL) {
		return  0;
	}
	else {
		s = 1 + AVL::size(p->left) + AVL::size(p->right);
	}
	return s;
}

int AVL::height(const std::shared_ptr<Vertex>& p) {
	int h = 0;
	if (p == NULL) {
		return h;
	}
	else {
		h = 1 + std::max(AVL::height(p->left), AVL::height(p->right));
		p->H = h;
	}
	return h;
}

void AVL::LL_turn(std::shared_ptr<Vertex>& p)
{
	std::shared_ptr<Vertex> q = p->left;
	p->bal = 0;
	q->bal = 0;
	p->left = q->right;
	q->right = p;
	p = std::move(q);
}

void AVL::LL1_turn(std::shared_ptr<Vertex>& p, int dec)
{
	std::shared_ptr<Vertex> q = p->left;
	if (q->bal == 0)
	{
		q->bal = 1;
		p->bal = -1;
		dec = 0;
	}
	else
	{
		q->bal = 0;
		p->bal = 0;
	}
	p->left = q->right;
	q->right = p;
	p = std::move(q);
}

void AVL::RR_turn(std::shared_ptr<Vertex>& p)
{
	std::shared_ptr<Vertex> q = p->right;
	p->bal = 0;
	q->bal = 0;
	p->right = q->left;
	q->left = p;
	p = std::move(q);
}

void AVL::RR1_turn(std::shared_ptr<Vertex>& p, int dec)
{
	std::shared_ptr<Vertex> q = p->right;
	if (q->bal == 0)
	{
		q->bal = 1;
		p->bal = -1;
		dec = 0;
	}
	else
	{
		q->bal = 0;
		p->bal = 0;
	}
	p->right = q->left;
	q->left = p;
	p = std::move(q);
}

void AVL::LR_turn(std::shared_ptr<Vertex>& p)
{
	if (!p || !p->left)
	{
		// Проверка на nullptr для p или p->left
		return;
	}

	std::shared_ptr<Vertex> q = p->left;
	if (!q->right)
	{
		// Проверка на nullptr для q->right
		return;
	}

	std::shared_ptr<Vertex> r = q->right;

	if (r->bal < 0)
	{
		p->bal = 1;
	}
	else
	{
		p->bal = 0;
	}

	if (r->bal > 0)
	{
		q->bal = -1;
	}
	else
	{
		q->bal = 0;
	}

	r->bal = 0;
	q->right = r->left;
	p->left = r->right;
	r->left = q;
	r->right = p;

	p = std::move(r);
}



void AVL::RL_turn(std::shared_ptr<Vertex>& p)
{
	std::shared_ptr<Vertex> q = p->right;
	std::shared_ptr<Vertex> r = q->left;
	if (r->bal < 0)
	{
		q->bal = 1;
	}
	else
	{
		q->bal = 0;
	}
	if (r->bal > 0)
	{
		p->bal = -1;
	}
	else
	{
		p->bal = 0;
	}
	r->bal = 0;
	q->left = r->right;
	p->right = r->left;
	r->right = q;
	r->left = p;
	p = std::move(r);
}
AVL::AVL(std::shared_ptr<Vertex>& p)
	{
		dec = 0;
		rost = 0;
		p = nullptr;
	}

std::shared_ptr<Vertex>& AVL::getRoot() {
		return root;
	}

void AVL::insert(std::string rus, std::string eng, std::shared_ptr<Vertex>& p) {
		dec = 0;
		rost = 0;

		if (p == NULL)
		{
			p = std::make_shared<Vertex>();
			p->englishWord = rus;
			p->russianWord = eng;
			p->left = NULL;
			p->right = NULL;
			p->bal = 0;
			rost = 1;
		}
		else if (rus < p->englishWord)
		{
			AVL::insert(rus, eng, p->left);
			if (rost == 1)
			{
				if (p->bal > 0)
				{
					p->bal = 0;
					rost = 0;
				}
				else if (p->bal == 0)
				{
					p->bal = -1;
					rost = 1;
				}
				else
				{
					if (p->left->bal < 0)
					{
						AVL::LL_turn(p);
						rost = 0;
					}
					else
					{
						AVL::LR_turn(p);
						rost = 0;
					}
				}
			}
		}
		else if (rus > p->englishWord)
		{
			AVL::insert(rus, eng, p->right);
			if (rost == 1)
			{
				if (p->bal < 0)
				{
					p->bal = 0;
					rost = 0;
				}
				else if (p->bal == 0)
				{
					p->bal = 1;
					rost = 1;
				}
				else
				{
					if (p->right->bal > 0)
					{
						AVL::RR_turn(p);
						rost = 0;
					}
					else
					{
						AVL::RL_turn(p);
						rost = 0;
					}
				}
			}
		}
	}

void AVL::BL(std::shared_ptr<Vertex>& p, int dec)
	{
		if (p->bal == -1) p->bal = 0;
		else if (p->bal == 0)
		{
			p->bal = 1;
			dec = 0;
		}
		else if (p->bal == 1)
		{
			if (p->right->bal >= 0) AVL::RR1_turn(p, dec);
			else AVL::RL_turn(p);
		}
	}

void AVL::BR(std::shared_ptr<Vertex>& p, int dec)
	{
		if (p->bal == 1) p->bal = 0;
		else if (p->bal == 0)
		{
			p->bal = -1;
			dec = 0;
		}
		else if (p->bal == -1)
		{
			if (p->left->bal <= 0) AVL::LL1_turn(p, dec);
			else AVL::LR_turn(p);
		}
	}

void AVL::del(std::shared_ptr<Vertex>& r, int dec, std::shared_ptr<Vertex>& q)
	{
		if (r->right != NULL)
		{
			AVL::del(r->right, dec, q);
			if (dec == 1) AVL::BR(r, dec);
		}
		else
		{
			q->englishWord = r->englishWord;
			q->russianWord = r->russianWord;
			q = r;
			r = r->left;
			dec = 1;
		}
	}

void AVL::obhod1(const std::shared_ptr<Vertex>& p) {
		if (p != NULL) {
			std::cout << p->englishWord << " " << p->russianWord << " ";
			AVL::obhod1(p->left);
			AVL::obhod1(p->right);
		}
	}
	
void AVL::obhod2(const std::shared_ptr<Vertex>& p) {
		if (p != NULL) {
			AVL::obhod2(p->left);
			AVL::obhod2(p->right);
			std::cout << p->englishWord << " " << p->russianWord << " ";
		}
	}

void AVL::obhod3(const std::shared_ptr<Vertex>& p, int& count, int currentPage, int pageSize, int& currentDisplayCount) {
		if (p != nullptr && currentDisplayCount < pageSize) {
			AVL::obhod3(p->left, count, currentPage, pageSize, currentDisplayCount);

			if (currentDisplayCount < pageSize) {
				if (count >= (currentPage - 1) * pageSize + 1) {
					std::cout << count << ". " << p->englishWord << " " << p->russianWord << std::endl;
					currentDisplayCount++;
				}
				count++;
			}

			AVL::obhod3(p->right, count, currentPage, pageSize, currentDisplayCount);
		}
	}

void AVL::display(std::shared_ptr<Vertex>& root, unsigned int currentPage, unsigned int pageSize, unsigned int totalNumberOfPages) {
		int count = 1;
		int currentDisplayCount = 0;
		std::cout << "Страница: " << currentPage << "/" << totalNumberOfPages << std::endl;
		AVL::obhod3(root, count, currentPage, pageSize, currentDisplayCount);
		std::cout << std::endl;
	}

void AVL::print(const std::string& prefix, std::shared_ptr<Vertex>& root, bool isLeft, std::ostream& os)
	{
		if (root != nullptr)
		{
			os << prefix;
			os << (isLeft ? "Л|-- " : "ПL__ ");
			os << root->englishWord << ", " << root->russianWord << std::endl;

			AVL::print(prefix + (isLeft ? "|  " : "    "), root->left, true, os);
			AVL::print(prefix + (isLeft ? "|  " : "    "), root->right, false, os);
		}
	}

void AVL::print(std::shared_ptr<Vertex>& root, std::ostream& os)
	{
		AVL::print("", root, false, os);
	}

std::string AVL::toLower(const std::string& str) {
		std::string result = str;
		std::transform(result.begin(), result.end(), result.begin(), [](unsigned char c) { return std::tolower(c); });
		return result;
	}

void AVL::searchHelper(const std::shared_ptr<Vertex>& current, const std::string& substr, std::vector<std::string>& result) {
		if (current == nullptr) {
			return;
		}

		std::string russianLower = toLower(current->englishWord);
		std::string englishLower = toLower(current->russianWord);

		if (russianLower.find(toLower(substr)) != std::string::npos) {
			result.push_back(current->englishWord + " " + current->russianWord);
		}

		if (englishLower.find(toLower(substr)) != std::string::npos) {
			result.push_back(current->englishWord + " " + current->russianWord);
		}

		AVL::searchHelper(current->left, substr, result);
		AVL::searchHelper(current->right, substr, result);
	}

void AVL::search(const std::shared_ptr<Vertex>& root, const std::string& substr, std::vector<std::string>& result) {
		searchHelper(root, substr, result);
	}


void AVL::searchHelper2(const std::shared_ptr<Vertex>& current, const std::string& substr, std::vector<std::string>& result) {
		if (current == nullptr) {
			return;
		}

		if (current->englishWord == substr) {
			result.push_back(current->englishWord + " " + current->russianWord);
			return;
		}

		if (substr < current->englishWord) {
			AVL::searchHelper2(current->left, substr, result);
		}

		if (substr > current->englishWord) {
			AVL::searchHelper2(current->right, substr, result);
		}
	}

void AVL::search2(const std::shared_ptr<Vertex>& root, const std::string& substr, std::vector<std::string>& result) {
		searchHelper2(root, substr, result);
	}

bool AVL::startsWith(const std::string& str, const std::string& prefix) {
		return str.compare(0, prefix.length(), prefix) == 0;
	}

bool AVL::findWordCount(const std::shared_ptr<Vertex>& p, const std::string& substr, int& currentWordNumber, int& wordCount) {
		if (p != nullptr) {
			if (AVL::findWordCount(p->left, substr, currentWordNumber, wordCount)) {
				return true;
			}

			currentWordNumber++;
			if (AVL::startsWith(p->englishWord, substr)) {
				wordCount = currentWordNumber;
				return true;
			}

			if (p->russianWord.find(substr) != std::string::npos) {
				wordCount = currentWordNumber;
				return true;
			}

			return AVL::findWordCount(p->right, substr, currentWordNumber, wordCount);
		}

		return false;
	}

int AVL::findPageNumber(const std::shared_ptr<Vertex>& p, const std::string& substr, int N) {
		int currentWordNumber = 1;
		int wordCount = 0;

		if (!findWordCount(p, substr, currentWordNumber, wordCount)) {
			return -1;
		}

		int pageNumber = ceil(wordCount / static_cast<double>(N));

		return pageNumber;
	}

void displayMenu() {
		std::cout << "=== РУССКО-АНГЛИЙСКИЙ СЛОВАРЬ ===\n";
		std::cout << "1. Найти английское слово\n";
		std::cout << "2. Найти слово по подстроке\n";
		std::cout << "3. Открыть словарь\n";
		std::cout << "4. Выход\n";
		std::cout << "================================\n";
	}

void displayAdditionalMenu() {
		std::cout << "=== УПРАВЛЕНИЕ СЛОВАРЕМ ===\n";
		std::cout << "1. Вперед\n";
		std::cout << "2. Назад\n";
		std::cout << "3. Перейти на страницу\n";
		std::cout << "4. Найти английское слово\n";
		std::cout << "5. Вернуться в предыдущее меню\n";
		std::cout << "================================\n";
	}

std::string replaceTabsWithSpaces(const std::string& str) {
		std::string result = str;
		std::replace(result.begin(), result.end(), '\t', ' ');
		return result;
	}

std::string removeCarriageReturns(const std::string& str) {
		std::string result = str;
		result.erase(std::remove(result.begin(), result.end(), '\r'), result.end());
		return result;
	}